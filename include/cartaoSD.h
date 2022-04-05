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
    bool listDir( const char * dirname, uint8_t levels, fs::FS &fs = SD_MMC);
    bool createDir(const char * path, fs::FS &fs = SD_MMC);
    bool removeDir(const char * path, fs::FS &fs = SD_MMC);
    bool readFile(const char * path, fs::FS &fs = SD_MMC);
    bool writeFile(const char * path, const char * message, fs::FS &fs = SD_MMC);
    bool appendFile(const char * path, const char * message, fs::FS &fs = SD_MMC);
    bool renameFile(const char * path1, const char * path2, fs::FS &fs = SD_MMC);
    bool deleteFile(const char * path, fs::FS &fs = SD_MMC);
    bool testFileIO(const char * path, fs::FS &fs = SD_MMC);

    private:

};

#endif