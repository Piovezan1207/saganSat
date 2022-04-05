#include "cartaoSD.h"

//Métodos retirados desse exemplo -> https://gist.github.com/youjunjer/b70b6e54ae7201a46387b8e73894ba51

bool operacoesSD::begin(){ //Inicialização do SD
    if(!SD_MMC.begin()){
        Serial.println("Falha na inicialização do cartão.");
        return false;
    }
    else return true;
}

bool operacoesSD::listDir( const char * dirname, uint8_t levels, fs::FS &fs){
    Serial.printf(" Listando diretórios: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Faha ao abrir o diretório.");
        return false;
    }
    if(!root.isDirectory()){
        Serial.println("Não é um diretório.");
        return false;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir( file.name(), levels -1, fs);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
    return true;
}

bool operacoesSD::createDir( const char * path, fs::FS &fs){
    Serial.printf("Criando diretório: %s\n", path);
    if(fs.mkdir(path)){
        Serial.println("Diretório criado");
        return true;
    } else {
        Serial.println("Criação do diretório falhou");
        return false;
    }
}

bool operacoesSD::removeDir( const char * path, fs::FS &fs){
    Serial.printf("Removendo diretório: %s\n", path);
    if(fs.rmdir(path)){
        Serial.println("Diretório removido");
        return true;
    } else {
        Serial.println("A remoção do diretório falhou");
        return false;
    }
}

bool operacoesSD::readFile( const char * path, fs::FS &fs){
    Serial.printf("Lendo arquivo: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Falaha ao abrir arquivo para leitura.");
        return false;
    }

    Serial.print("Leitura do arquivo: ");
    while(file.available()){
        Serial.write(file.read());
    }
    return true;
}

bool operacoesSD::writeFile( const char * path, const char * message, fs::FS &fs){
    Serial.printf("Escrevendo no arquivo: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Falha ao abrir arquivo para leitura.");
        return false;
    }
   
 
   //fwrite(fb->buf, 1, fb->len, file);
    if(file.print(message)){
        Serial.println("Arquivo escrito.");
    } else {
        Serial.println("Escrita falhou.");
    }
    return true;
}

bool operacoesSD::appendFile( const char * path, const char * message, fs::FS &fs){
    Serial.printf("Adicionando ao arquivo: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Falha ao abrir o arquivo para adicionar.");
        return false;
    }
    if(file.print(message)){
        Serial.println("Mensagem adicionada ao arquivo.");
        return true;
    } else {
        Serial.println("Falha ao adicionar mensagem.");
        return false;
    }
}

bool operacoesSD::renameFile( const char * path1, const char * path2, fs::FS &fs){
    Serial.printf("Renomeando arquivo %s para %s\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("Arquivo renomeado.");
        return true;
    } else {
        Serial.println("Falha ao renomear.");
        return false;
    }
}

bool operacoesSD::deleteFile( const char * path, fs::FS &fs){
    Serial.printf("Apagando arquivo: %s\n", path);
    if(fs.remove(path)){
        Serial.println("Arquivo apagado.");
        return true;
    } else {
        Serial.println("Falha ao apagar arquivo.");
        return false;
    }
}

bool operacoesSD::testFileIO( const char * path, fs::FS &fs){
    File file = fs.open(path);
    static uint8_t buf[512];
    size_t len = 0;
    uint32_t start = millis();
    uint32_t end = start;
    if(file){
        len = file.size();
        size_t flen = len;
        start = millis();
        while(len){
            size_t toRead = len;
            if(toRead > 512){
                toRead = 512;
            }
            file.read(buf, toRead);
            len -= toRead;
        }
        end = millis() - start;
        Serial.printf("%u bytes lidos para %u ms\n", flen, end);
        file.close();
    } else {
        Serial.println("Falha ao abrir arquivo para leitura.");
        // return false;
    }


    file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Falha ao abrir arquivo para escrita.");
        return false;
    }

    size_t i;
    start = millis();
    for(i=0; i<2048; i++){
        file.write(buf, 512);
    }
    end = millis() - start;
    Serial.printf("%u bytes escritos para %u ms\n", 2048 * 512, end);
    file.close();
    return true;
}

/* Exemplo desses métodos sendo utilizados em um loop
 uint8_t cardType = SD_MMC.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD_MMC card attached");
        return;
    }

    Serial.print("SD_MMC Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
    Serial.printf("SD_MMC Card Size: %lluMB\n", cardSize);

    listDir(SD_MMC, "/", 0);
    createDir(SD_MMC, "/mydir");
    listDir(SD_MMC, "/", 0);
    removeDir(SD_MMC, "/mydir");
    listDir(SD_MMC, "/", 2);
    writeFile(SD_MMC, "/hello.txt", "Hello ");
    appendFile(SD_MMC, "/hello.txt", "World!\n");
    readFile(SD_MMC, "/hello.txt");
    deleteFile(SD_MMC, "/foo.txt");
    renameFile(SD_MMC, "/hello.txt", "/foo.txt");
    readFile(SD_MMC, "/foo.txt");
    testFileIO(SD_MMC, "/test.txt");
    Serial.printf("Total space: %lluMB\n", SD_MMC.totalBytes() / (1024 * 1024));
    Serial.printf("Used space: %lluMB\n", SD_MMC.usedBytes() / (1024 * 1024));  
*/