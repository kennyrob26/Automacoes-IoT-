#ifndef _MANIPULACAO_DE_ARQUIVOS_
    #define _MANIPULACAO_DE_ARQUIVOS

    #include <SPIFFS.h>

    //
    void iniciairSPIFFS();

    //Retorna o conteúdo presente no caminho "localArquivo" exemplo /texto.txt
    String lerArquivo(fs::FS &fs, const char* localArquivo);

    //Escreve "conteudo" no arquivo presente em "caminhoArquivo"
    void escreverArquivo(fs::FS &fs, const char* caminhoArquivo, const char* conteudo);
#endif