#include "Arduino.h"
#include "FS.h" 
#include "SD_MMC.h"

#ifndef cartaoSD
#define cartaoSD

class operacoesSD{

    /*  
        Métodos da classe de possíveis operações com o cartão SD
    */
    public:
    bool begin();
    bool listDir(fs::FS &fs, const char * dirname, uint8_t levels);
    bool createDir(fs::FS &fs, const char * path);
    bool removeDir(fs::FS &fs, const char * path);
    bool readFile(fs::FS &fs, const char * path);
    bool writeFile(fs::FS &fs, const char * path, const char * message);
    bool appendFile(fs::FS &fs, const char * path, const char * message);
    bool renameFile(fs::FS &fs, const char * path1, const char * path2);
    bool deleteFile(fs::FS &fs, const char * path);
    bool testFileIO(fs::FS &fs, const char * path);

    private:

};

#endif