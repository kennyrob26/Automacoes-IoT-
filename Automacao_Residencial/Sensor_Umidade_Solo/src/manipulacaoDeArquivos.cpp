/*=====================================================

    *Estão presente todas as funções para manipulação de arquivos
    *Estas funções tem grande utilização na configuração do projeto
    *Elas são muito utilizadas no arquivo configWifi.cpp

======================================================*/


#include "manipulacaoDeArquivos.h"

//Inicia o montador SPIFFS
void iniciairSPIFFS()
{
  if(!SPIFFS.begin(true))
  {
    Serial.println("Erro ao tentar montar SPIFFS");
  }
  Serial.println("SPIFFS foi montado com sucesso");
}

//Recebe um arquivo e retorna seu conteúdo
String lerArquivo(fs::FS &fs, const char* localArquivo)
{
  Serial.printf("Vamos iniciar a leitura do arquivo: %s\r\n", localArquivo);
  File arquivo = fs.open(localArquivo, "r");   //r significa que será feita a leitura
  if(!arquivo || arquivo.isDirectory())
  {
    Serial.println("Não foi possível ler o arquivo");
    return String();
  }
  Serial.println("Lendo o arquivo:");

  String conteudoArquivo;
  while(arquivo.available())
  {
    conteudoArquivo = arquivo.readStringUntil('\n');
    break;
  }

  return conteudoArquivo;
}

//Recebe um arquivo e escreve um conteúdo
void escreverArquivo(fs::FS &fs, const char* caminhoArquivo, const char* conteudo)
{
  Serial.printf("Iniciando a escrita no arquivo: %s\r\n", caminhoArquivo);
  File arquivo = fs.open(caminhoArquivo, "w");  //w significa que vamos escrever
  if(!arquivo){
    Serial.println("Não foi possível escrever no arquivo!");
    return;
  }
  if(arquivo.print(conteudo))
  {
    Serial.println("A escrita foi bem sucedida");
  }
  else
  {
    Serial.println("Falha ao tentar escrever no arquivo");
  }
  arquivo.close();
}

