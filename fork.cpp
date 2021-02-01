#include <iostream>
#include <time.h>
#include <sys/types.h>
#include <unistd.h> 
#include <sys/wait.h>

using namespace std;

struct tm* nascimento[5];

//pega a hora atual em um objeto tm (acessa por -> os atributos de tempo dentro do objeto)
struct tm* pegar_hora_atual() {
  struct tm *hora_atual;
  time_t segundos;
  return localtime(&segundos);
}

int tempoDeVida(struct tm* n,struct tm* m){  
  return (m->tm_hour*60*60 + m->tm_min*60 + m->tm_sec) - (n->tm_hour*60*60 + n->tm_min*60 + n->tm_sec);
}

void mataUmNo(string no,string pai,int id){
  struct tm* hm = pegar_hora_atual();
  cout<<"Morte do nó "<<no<<" Filho do nó "<<pai;
  cout<<" na hora "<<hm->tm_hour<<":"<<hm->tm_min<<":"<<hm->tm_sec;
  cout<<" hora de nascimento "<<nascimento[id]->tm_hour<<":"<<nascimento[id]->tm_min<<":"<<nascimento[id]->tm_sec;
  cout<<" tempo de vida em segundos "<<tempoDeVida(nascimento[id],hm); 
  cout<<endl;
}

void criarUmFilho(string no,string pai,struct tm* hora,int id){
  hora = pegar_hora_atual();
  cout<<"Nascimento do nó "<<no<<" Filho do nó "<<pai;
  cout<<" hora "<<hora->tm_hour<<":"<<hora->tm_min<<":"<<hora->tm_sec;
  cout<<endl;
  nascimento[id] = hora;
}

int main() {
  
  struct tm* hora = pegar_hora_atual();
  //armazenar os valores de retorno dos processos criados
  int processos[5] = {-1};

  cout<<"Nascimento do  nó PAI  na hora  "<<hora->tm_hour<<":"<<hora->tm_min<<":"<<hora->tm_sec;
  cout<<endl;
  nascimento[0] = hora;

  processos[0] = fork();
  if(processos[0]>0){
    sleep(14);
    criarUmFilho("FILHO1", "PAI", hora,1);
    sleep(2);
    criarUmFilho("PAI", "PAI", hora,2);
    processos[1] = fork();
    if(processos[1] > 0){
      sleep(10);
      criarUmFilho("NETO1", "FILHO1",hora,3);
      processos[2] = fork();
      if(processos[2]>0){
        sleep(4);
        criarUmFilho("FILHO2", "PAI",hora,4);
        sleep(2);
        criarUmFilho("PAI","PAI",hora,5);
        processos[3] = fork();
        if(processos[3]>0){
          sleep(6);
          mataUmNo("NETO1","FILHO1",3);
          sleep(4);
          criarUmFilho("NETO2","FILHO2", hora,6);
          sleep(2);
          mataUmNo("FILHO1","PAI",1);
          sleep(2); 
          criarUmFilho("FILHO2","FILHO2",hora,7);
          sleep(12);
          mataUmNo("FILHO2","PAI",4);
          sleep(4);
          mataUmNo("NETO2","FILHO2",6);
          sleep(24);
          mataUmNo("FILHO2","FILHO2",7);
          
          
        }

      }
      if(!processos[2]){
        criarUmFilho("FILHO1", "FILHO1", hora,8);
        sleep(30);
        mataUmNo("FILHO1","FILHO1",8);
      }
      

    }
  
  }

  return 0;
}
