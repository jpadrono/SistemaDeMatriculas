#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define p printf
#define s scanf
#define PERIODO_ATUAL 2024.1
#define MAX_LINE_SIZE 300

//Declaração das structs para lsitas encadeadas

typedef struct _Aluno{
  int codigo;
  char nome[100], cpf[13];
  //ponteiros auxiliares para listagem encadeada dos dados
  struct _Aluno *prox;
  /****************************************************************************
   *  O ponteiro *ant será usado apenas para debugagem do código              *
   * caso, ao fazer uma pesquisa na lista, o ptr *ant não começar apontado    *
   * para NULL, significa que eu não comecei a busca no primeiro elemento     *
   * e portanto devemos parar o código                                        *
   ****************************************************************************/
  struct _Aluno *ant;
} Aluno;

//
Aluno *ptr_i_aluno = NULL;

typedef struct _Disciplina{
  int codigo, creditos;
  char nome[100], professor[100];
  struct _Disciplina *prox;
  struct _Disciplina *ant;
} Disciplina;

Disciplina *ptr_i_disciplina = NULL;

typedef struct _Matricula{
  int aluno, disciplina;
  int periodo;
  struct _Matricula *prox;
  struct _Matricula *ant;
} Matricula;

Matricula *ptr_i_matricula = NULL;

//Declaração de variáveis
/******************************************************************************
 *  Para códigos grandes, uma boa sequência de ações é começar declarando as  *
 * principais funções que serão necessárias para o código, em seguida,        *
 * estruturar a lógica do código na main e por fim, escrever a lógica das     *
 * funções no finla do código.                                                *
 ******************************************************************************/

void criar_matricula(Matricula **ptr, int periodo, int aluno, int disciplina);
void criar_aluno(Aluno **ptr, char *nome, char *cpf, int codigo);
void criar_disciplina(Disciplina **ptr, char *nome, char *professor, int creditos, int codigo);
void inserir_aluno_na_disciplina();
void inserir_disciplina_no_aluno();
void remover_matricula(Matricula **ptr);
void remover_aluno(Aluno **ptr, Matricula **ptr2);
void remover_disciplina(Disciplina **ptr, Matricula **ptr2);
void listar_alunos_por_periodo(); //dispensável
void listar_disciplinas_por_periodo(); //dispensável
void consultar_disciplinas_por_aluno(Matricula **ptr);
void consultar_alunos_por_disciplina(Matricula **ptr);
int verificar_cpf(char*ptr);
int verificar_periodo(int periodo);
int verificar_codigo_disciplina(int codigo);
int verificar_codigo_aluno(int codigo);
int buscar_aluno(int codigo, Aluno **ptr);
int buscar_disciplina(int codigo, Disciplina **ptr);
void liberar();
void salvar(FILE *ptr, Aluno *ptr_aluno, Disciplina *ptr_disciplina, Matricula* ptr_matricula);
void recuperar(FILE *arq);
/******************************************************************************
 * nesse começo de código, vamos considerar que serão feitas apenas cadastros *
 * válidos, porém é interessante colocar algumas funções de validação,        *
 * principalmente para os códigos e para o período                            *  
 ******************************************************************************/


//declaração de variáveis globais
FILE *fptr;



int main (){
  //primeiro passoda main: recurar os dados salvos
  recuperar(fptr);
  p("\t\tSISTEMA DE MATRÍCULAS\t\t\n");
  //variáveis para controle da opção escolhida em cada menu
  int op1, op2;
  do{
    p("escolha uma opção:\n");
    p("1- Criar\n");
    p("2- Inserção\n");
    p("3- Remoção\n");
    p("4- Consulta\n");
    p("0- Salvar e sair\n");
    s(" %d", &op1);
    /**************************************************************************
     * getchar é usado para pegar o char do buffer, no caso do usuário digitar*
     * uma letra, sem ele o menu entraria num loop infinito                   *
     **************************************************************************/
    getchar();

    if(op1 < 0 || op1 > 4){
      p("op1 recebeu um valor inválido\n");
    }

    switch(op1){
      case 1:
        do{
          p("escolha uma opção:\n");
          p("1- Criar nova ficha de aluno\n");
          p("2- Criar nova ficha de disciplina\n");
          p("0- voltar para o menu principal\n");
          s(" %d", &op2);
          getchar();

          switch(op2){
            case 0:
              break;
            case 1:
              criar_aluno(&ptr_i_aluno, "", "", 0);
              break;
            case 2:
              criar_disciplina(&ptr_i_disciplina, "", "", 0, 0);
              break;
            default:
              p("Opção inválida\n");
              break;
          }
        }while(op2);
        break;
      case 2:
        do{
          p("escolha uma opção:\n");
          p("1- Inserir novos alunos para disciplina\n");
          p("2- Inserir novas disciplinas para aluno\n");
          p("0- voltar para o menu principal\n");
          s(" %d", &op2);
          getchar();


          switch(op2){
            case 0:
              break;
            case 1:
              inserir_aluno_na_disciplina();
              break;
            case 2:
              inserir_disciplina_no_aluno();
              break;
            default:
              p("Opção inválida\n");
              break;
          }
        }while(op2);
        break;
      case 3:
        do{
          p("escolha uma opção:\n");
          p("1- Remover matricula de aluno\n");
          p("2- Remover Ficha de aluno\n");
          p("3- Remover Fciha de disciplina\n");
          p("0- voltar para o menu principal\n");
          s(" %d", &op2);
          getchar(); 

          switch(op2){
            case 0:
              break;
            case 1:
              remover_matricula(&ptr_i_matricula);
              break;
            case 2:
              remover_aluno(&ptr_i_aluno, &ptr_i_matricula);
              break;
            case 3:
              remover_disciplina(&ptr_i_disciplina, &ptr_i_matricula);
              break;
            default:
              p("Opção inválida\n");
              break;
          }
        }while(op2);
        break; 
      case 4:
        do{
          p("escolha uma opção:\n");
          p("1- Consultar disciplinas de um aluno\n");
          p("2- Consultar alunos matriculados em uma disciplina\n");
          p("0- voltar para o menu principal\n");
          s(" %d", &op2);
          getchar(); 

          switch(op2){
            case 0:
              break;
            case 1:
              consultar_disciplinas_por_aluno(&ptr_i_matricula);
              break;
            case 2:
              consultar_alunos_por_disciplina(&ptr_i_matricula);
              break;
            default:
              p("Opção inválida\n");
              break;
          }
        }while(op2);
        break; 
      
    }
    
  }while(op1);

  //antes de finalizar a main: salvar os dados e liberar as alocações
  salvar(fptr, ptr_i_aluno, ptr_i_disciplina, ptr_i_matricula);
  liberar(ptr_i_aluno, ptr_i_disciplina, ptr_i_matricula);
  return 0;
}

//lógica das funções
/******************************************************************************
 * Perceba que no início de cada função tem um print com o nome da função     *
 * após a criação da lógica da main e antes da criação da lógica das funções  *
 * rodo o programa uma vez para testes, e para isso, preciso que as funções   *
 * tenham algum retorno para eu saber se elas estão sendo chamadas            *
 ******************************************************************************/

void criar_matricula(Matricula **ptr, int periodo, int aluno, int disciplina){
  // ponteiro de controle para ordenar a lista encadeada
  // as variaveis serao ordenadas no momento da criacao
  // significado: new_ptr e old_ptr;
  Matricula *n_ptr, *o_ptr, *ptr_aux;

  n_ptr = (Matricula*)malloc(sizeof(Matricula));
  if(!n_ptr){
    p("Erro na alocação!\n");
    return;
  }

  //coleta dos dados
  if(periodo){
    n_ptr->periodo = periodo;
    n_ptr->aluno = aluno;
    n_ptr->disciplina = disciplina;
  }else{
    float var;
    do{
      p("digite o período:\n");
      s(" %f", &var);
      getchar();
      n_ptr->periodo = (int)(var*10);    
    }while(verificar_periodo((int)(var*10)));

    do{
      p("digite o código do aluno:\n");
      s(" %d", &(n_ptr->aluno));
      getchar();
    }while(verificar_codigo_aluno(n_ptr->aluno) || !buscar_aluno(n_ptr->aluno, &ptr_i_aluno));

    do{
      p("digite o código do disciplina:\n");
      s(" %d", &(n_ptr->disciplina));
      getchar();
    }while(verificar_codigo_disciplina(n_ptr->disciplina) || !buscar_disciplina(n_ptr->disciplina, &ptr_i_disciplina));
  }

  //inserção na lista encadeada
  ptr_aux = *ptr;
  o_ptr = NULL;

  //caso seja o primeiro cadastro
  if(!ptr_aux){
    n_ptr->prox = NULL;
    n_ptr->ant = NULL;
    *ptr = n_ptr;
  } else {
    //mesmo principio do insertion sort
    //irei ordenar por periodo, codigo do aluno, codigo da disciplina
    while(
      ptr_aux && 
      ptr_aux->periodo < n_ptr->periodo
    ){
      o_ptr = ptr_aux;
      ptr_aux = ptr_aux->prox;
    }
    while(
      ptr_aux && 
      ptr_aux->periodo == n_ptr->periodo &&
      ptr_aux->aluno < n_ptr->aluno
    ){
      o_ptr = ptr_aux;
      ptr_aux = ptr_aux->prox;
    }
    while(
      ptr_aux && 
      ptr_aux->periodo == n_ptr->periodo &&
      ptr_aux->aluno == n_ptr->aluno &&
      ptr_aux->disciplina < n_ptr->disciplina 
    ){
      o_ptr = ptr_aux;
      ptr_aux = ptr_aux->prox;
    }

    if(ptr_aux && 
      ptr_aux->periodo == n_ptr->periodo &&
      ptr_aux->aluno == n_ptr->aluno &&
      ptr_aux->disciplina == n_ptr->disciplina
    ){
      p("Matricula já existente\n");
      return;
    }
    

    n_ptr->prox = ptr_aux;
    if(ptr_aux){
      ptr_aux->ant = n_ptr;
    }

    //caso em que o elemento será colocado como o primeiro da lista
    if(!o_ptr){
      *ptr = n_ptr;
      n_ptr->ant = NULL;
    } else{
      o_ptr->prox = n_ptr;
      n_ptr->ant = o_ptr;
    }
  }
  return;
}

void criar_aluno(Aluno **ptr, char* nome, char* cpf, int codigo){
  Aluno *n_ptr, *o_ptr, *ptr_aux;

  n_ptr = (Aluno*)malloc(sizeof(Aluno));
  if(!n_ptr){
    p("Erro na alocação!\n");
    return;
  }

  if(codigo){
    strcpy(n_ptr->nome, nome);
    strcpy(n_ptr->cpf, cpf);
    n_ptr->codigo = codigo;
  }else{
    char string_var[100];
    p("digite o nome do aluno:\n");
    s(" %[^\n]", string_var);
    strcpy(n_ptr->nome, string_var);
    do{
      p("digite o cpf do aluno no formato XXXXXXXXX-XX:\n");
      s(" %[^\n]", string_var);
    }
    while(verificar_cpf(string_var));
    strcpy(n_ptr->cpf, string_var);

    do{
      p("digite o código do aluno:\n");
      s(" %d", &(n_ptr->codigo));
      getchar();
    }while(verificar_codigo_aluno(n_ptr->codigo));
  }


  ptr_aux = *ptr;
  o_ptr = NULL;

  if(!ptr_aux){
    n_ptr->prox = NULL;
    n_ptr->ant = NULL;
    *ptr = n_ptr;
  } else {
    while(
      ptr_aux && 
      ptr_aux->codigo < n_ptr->codigo
    ){
      o_ptr = ptr_aux;
      ptr_aux = ptr_aux->prox;
    }

    if(ptr_aux && ptr_aux->codigo == n_ptr->codigo){
      p("aluno já cadastrado\n");
      return;
    }

    n_ptr->prox = ptr_aux;
    if(ptr_aux){
      ptr_aux->ant = n_ptr;
    }


    if(!o_ptr){
      *ptr = n_ptr;
      n_ptr->ant = NULL;
    } else{
      o_ptr->prox = n_ptr;
      n_ptr->ant = o_ptr;
    }
  }
  return;
}

void criar_disciplina(Disciplina **ptr, char*nome, char* professor, int creditos, int codigo){
  Disciplina *n_ptr, *o_ptr, *ptr_aux;

  n_ptr = (Disciplina*)malloc(sizeof(Disciplina));
  if(!n_ptr){
    p("Erro na alocação!\n");
    return;
  }

  if(codigo){
    strcpy(n_ptr->nome, nome);
    strcpy(n_ptr->professor, professor);
    n_ptr->creditos = creditos;
    n_ptr->codigo = codigo;
  }else{
    char string_var[100];
    p("digite o nome da disciplina:\n");
    s(" %[^\n]", string_var);
    strcpy(n_ptr->nome, string_var);

    p("digite o nome do professor:\n");
    s(" %[^\n]", string_var);
    strcpy(n_ptr->professor, string_var);

    p("digite os créditos da disciplina:\n");
    s(" %d", &(n_ptr->creditos));
    getchar();

    do{
      p("digite o código da disciplina:\n");
      s(" %d", &(n_ptr->codigo));
      getchar();
    }while(verificar_codigo_disciplina(n_ptr->codigo));
  }

  ptr_aux = *ptr;
  o_ptr = NULL;

  if(!ptr_aux){
    n_ptr->prox = NULL;
    n_ptr->ant = NULL;
    *ptr = n_ptr;
  } else {
    while(
      ptr_aux && 
      ptr_aux->codigo < n_ptr->codigo
    ){
      o_ptr = ptr_aux;
      ptr_aux = ptr_aux->prox;
    }

    if(ptr_aux &&
     ptr_aux->codigo == n_ptr->codigo){
      p("disciplina já cadastrada\n");
      return;
    }

    n_ptr->prox = ptr_aux;
    if(ptr_aux){
      ptr_aux->ant = n_ptr;
    }

    if(!o_ptr){
      *ptr = n_ptr;
      n_ptr->ant = NULL;
    } else{
      o_ptr->prox = n_ptr;
      n_ptr->ant = o_ptr;
    }
  }
  return;
}


void inserir_aluno_na_disciplina(){
  criar_matricula(&ptr_i_matricula, 0, 0, 0);
}
void inserir_disciplina_no_aluno(){
  criar_matricula(&ptr_i_matricula, 0, 0, 0);
}

void remover_matricula(Matricula **ptr){
  Matricula *o_ptr, *ptr_aux;
  float var;
  int al_aux, dis_aux, per_aux;

  o_ptr = NULL;
  ptr_aux = *ptr;

  p("digite o periodo em que deseja cancelar a matricula\n");
  s(" %f", &var);
  per_aux = (int)(var*10);

  p("digite o código do aluno deseja cancelar a matricula\n");
  s(" %d", &al_aux);

  p("digite o código da disciplina que deseja cancelar a matricula\n");
  s(" %d", &dis_aux);

  while(
    ptr_aux && 
    ptr_aux->periodo < per_aux
  ){
    o_ptr = ptr_aux;
    ptr_aux = ptr_aux->prox;
  }
  while(
    ptr_aux && 
    ptr_aux->periodo == per_aux &&
    ptr_aux->aluno < al_aux
  ){
    o_ptr = ptr_aux;
    ptr_aux = ptr_aux->prox;
  }
  while(
    ptr_aux && 
    ptr_aux->periodo == per_aux &&
    ptr_aux->aluno == al_aux &&
    ptr_aux->disciplina < dis_aux
  ){
    o_ptr = ptr_aux;
    ptr_aux = ptr_aux->prox;
  }

  if(
    ptr_aux->periodo == per_aux &&
    ptr_aux->aluno == al_aux &&
    ptr_aux->disciplina == dis_aux
  ){
    if(o_ptr == NULL){
      *ptr = ptr_aux->prox;
    }else{
      o_ptr->prox = ptr_aux->prox;
    }
    free(ptr_aux);
    p("Matricula removida com sucesso\n");
  }else{
    p("Matricula não encontrada\n");
  }

  return;
}

void remover_aluno(Aluno **ptr, Matricula **ptr2){
  p("chamada a função remover_aluno\n");
  Aluno *o_ptr, *ptr_aux;
  Matricula *o_ptr2, *ptr_aux2;
  int al_aux;

  o_ptr = NULL;
  ptr_aux = *ptr;

  o_ptr2 = NULL;
  ptr_aux2 = *ptr2;

  p("Digite o código do aluno que deseja remover\n");
  s(" %d", &al_aux);

//Removendo o aluno da lista de alunos
  while(
    ptr_aux &&
    ptr_aux->codigo < al_aux
  ){
    o_ptr = ptr_aux;
    ptr_aux = ptr_aux->prox;
  }
  if(
    ptr_aux->codigo == al_aux
  ){
    //caso seja removido o primeiro elemento
    if(o_ptr == NULL){
      *ptr = ptr_aux->prox;
    }else{
      o_ptr->prox = ptr_aux->prox;
    }
    free(ptr_aux);
    
    //Removendo o aluno todas as vezes que ele aparece na lista de matrícula
    while(ptr_aux2){
      while(ptr_aux2->aluno != al_aux){
        o_ptr2 = ptr_aux2;
        ptr_aux2 = ptr_aux2->prox;
        if(!ptr_aux2){
          break;
        }
      }
      if(ptr_aux2){
        while(ptr_aux2->aluno == al_aux){
          if(o_ptr2 == NULL){
            *ptr2 = ptr_aux2->prox;
            ptr_aux2 = ptr_aux2->prox;
          }else{
            ptr_aux2 = ptr_aux2->prox;
          }
          if(o_ptr2){
            o_ptr2->prox = ptr_aux2;
          }
          if(!ptr_aux2){
            break;
          }
        }
      }
    }
    p("Aluno removido com sucesso\n");
  }else{
    p("Aluno não encontrado\n");
  }
  return;
}

void remover_disciplina(Disciplina **ptr, Matricula **ptr2){
  Disciplina *o_ptr, *ptr_aux;
  Matricula *o_ptr2, *ptr_aux2;
  int dis_aux;

  o_ptr = NULL;
  ptr_aux = *ptr;

  o_ptr2 = NULL;
  ptr_aux2 = *ptr2;

  p("digite o código da disciplina que deseja cancelar a matricula\n");
  s(" %d", &dis_aux);
  getchar();

  while(
    ptr_aux &&
    ptr_aux->codigo < dis_aux  
  ){
    o_ptr = ptr_aux;
    ptr_aux = ptr_aux->prox;
  }

  if(
    ptr_aux->codigo == dis_aux
  ){
    if(o_ptr == NULL){
      *ptr = ptr_aux->prox;
    }else{
      o_ptr->prox = ptr_aux->prox;
    }
    free(ptr_aux);
    //Removendo a disciplina todas as vezes que ela aparece na lista de matrícula
    while(ptr_aux2){
      while(ptr_aux2->disciplina != dis_aux){
        o_ptr2 = ptr_aux2;
        ptr_aux2 = ptr_aux2->prox;
        if(!ptr_aux2){
          break;
        }
      }
      if(ptr_aux2){
        while(ptr_aux2->disciplina == dis_aux){
          if(o_ptr2 == NULL){
            *ptr2 = ptr_aux2->prox;
            ptr_aux2 = ptr_aux2->prox;
          }else{
            ptr_aux2 = ptr_aux2->prox;
          }
          if(o_ptr2){
            o_ptr2->prox = ptr_aux2;
          }
          if(!ptr_aux2){
            break;
          }
        }
      }
    }
    p("Disciplina removida com sucesso\n");
  }else{
    p("Disciplina não encontrada\n");
  }
  return;
}

void consultar_disciplinas_por_aluno(Matricula **ptr){
  Matricula *ptr_aux;
  float var;
  int al_aux, per_aux;

  ptr_aux = *ptr;

  p("Digite o período de matricula do aluno\n");
  s(" %f", &var);
  per_aux = (int)(var*10);

  p("Digite o código do aluno que deseja fazer a consulta\n");
  s(" %d", &al_aux);

  while(ptr_aux && ptr_aux->periodo < per_aux){
    ptr_aux = ptr_aux->prox;
  }
  while(ptr_aux && ptr_aux->periodo == per_aux && ptr_aux->aluno < al_aux){
    ptr_aux = ptr_aux->prox;
  }
  if(ptr_aux && ptr_aux->periodo == per_aux && ptr_aux->aluno == al_aux){
    p("Lista de disciplinas em que o aluno %d está matriculado no período %.1f\n", al_aux, var);
    int count = 0;
    while(ptr_aux && ptr_aux->periodo == per_aux && ptr_aux->aluno == al_aux){
      p("%d-\t%d\n", ++count, ptr_aux->disciplina);
      ptr_aux = ptr_aux->prox;
    }
  }else{
    p("O aluno não está matriculado em nenhuma disciplina no período fornecido\n");
  }
  return;
}

void consultar_alunos_por_disciplina(Matricula **ptr){
  Matricula *ptr_aux;
  float var;
  int dis_aux, per_aux;

  ptr_aux = *ptr;

  p("Digite o período de matricula do aluno\n");
  s(" %f", &var);
  per_aux = (int)(var*10);

  p("Digite o código da disciplina que deseja fazer a consulta\n");
  s(" %d", &dis_aux);

  while(ptr_aux && ptr_aux->periodo < per_aux){
    ptr_aux = ptr_aux->prox;
  }
  int count = 0;
  if(ptr_aux && ptr_aux->periodo == per_aux){
    while(ptr_aux && ptr_aux->periodo == per_aux){
      if(ptr_aux->disciplina == dis_aux){
        if(!count){
          p("Lista de alunos que estão matriculados na disicplina %d no período %.1f\n", dis_aux, var);
        }
        p("%d-\t%d\n", ++count, ptr_aux->aluno);
        ptr_aux = ptr_aux->prox;
      }else{
        ptr_aux = ptr_aux->prox;
      }
    }
  }
  if(!count){
    p("A disicplina nõa possui alunos cadastranso no período selecionado\n");
  }
  return;
}

void liberar(Aluno *ptr_aluno, Disciplina *ptr_disciplina, Matricula *ptr_matricula){
    if(ptr_aluno != NULL){
    while(ptr_aluno->prox != NULL){
      if(ptr_aluno->ant != NULL) free(ptr_aluno->ant);
      ptr_aluno = ptr_aluno->prox;
    }
    if(ptr_aluno->ant != NULL) free(ptr_aluno->ant);
    free(ptr_aluno);
  }

  if(ptr_disciplina != NULL){
    while(ptr_disciplina->prox != NULL){
      if(ptr_disciplina->ant != NULL) free(ptr_disciplina->ant);
      ptr_disciplina = ptr_disciplina->prox;
    }
    if(ptr_disciplina->ant != NULL) free(ptr_disciplina->ant);
    free(ptr_disciplina);
  }

  if(ptr_matricula != NULL){
    while(ptr_matricula->prox != NULL){
      if(ptr_matricula->ant != NULL) free(ptr_matricula->ant);
      ptr_matricula = ptr_matricula->prox;
    }
    if(ptr_matricula->ant != NULL) free(ptr_matricula->ant);
    free(ptr_matricula);
  }
}

/******************************************************************************
 * A ideia aqui vai ser salvar uma struct em cada linha, sendo que a primeira *
 * letra da linha indica se trata de uma matricula, aluno ou disciplina       *
 ******************************************************************************/
void salvar(FILE *arq, Aluno *ptr_aluno, Disciplina *ptr_disciplina, Matricula *ptr_matricula){
  arq = fopen("sistema_de_matricula.txt", "w");
  if (!arq) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  char tab = '\t', el = '\n'; 
  while(ptr_matricula){
    fputc('m',arq);
    fputc(tab, arq);
    fprintf(arq, "%d" , ptr_matricula->periodo);
    fputc(tab, arq);
    fprintf(arq, "%d" , ptr_matricula->aluno);
    fputc(tab, arq);
    fprintf(arq, "%d" , ptr_matricula->disciplina);
    fputc(tab, arq);
    fputc(el, arq);
    ptr_matricula = ptr_matricula->prox;
  }
  while(ptr_aluno){
    fputc('a',arq);
    fputc(tab, arq);
    fprintf(arq, "%s" , ptr_aluno->nome);
    fputc(tab, arq);
    fprintf(arq, "%s" , ptr_aluno->cpf);
    fputc(tab, arq);
    fprintf(arq, "%d" , ptr_aluno->codigo);
    fputc(tab, arq);
    fputc(el, arq);
    ptr_aluno = ptr_aluno->prox;
  }
  while(ptr_disciplina){
    fputc('d',arq);
    fputc(tab, arq);
    fprintf(arq, "%s" , ptr_disciplina->nome);
    fputc(tab, arq);
    fprintf(arq, "%d" , ptr_disciplina->creditos);
    fputc(tab, arq);
    fprintf(arq, "%s" , ptr_disciplina->professor);
    fputc(tab, arq);
    fprintf(arq, "%d" , ptr_disciplina->codigo);
    fputc(tab, arq);
    fputc(el, arq);
    ptr_disciplina = ptr_disciplina->prox;
  }
  fputc(el, arq);
  fclose(arq);
}

void recuperar(FILE *arq){
  arq = fopen("sistema_de_matricula.txt", "r");
  if (!arq) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }
  char linha[MAX_LINE_SIZE];

  int aluno, disciplina, codigo, creditos, periodo;
  char nome[100], cpf[13], professor[100];
  while (fgets(linha, sizeof(linha), arq)) {
    if (linha[0] == 'm') {
      sscanf(linha, "%*s%d%d%d", &periodo, &aluno, &disciplina);
      criar_matricula(&ptr_i_matricula, periodo, aluno, disciplina);
    } else if (linha[0] == 'a') {
      sscanf(linha, "%*s %[^0-9] %s%d", nome, cpf, &codigo);
      nome[strlen(nome)-1] = '\0';
      criar_aluno(&ptr_i_aluno, nome, cpf, codigo);
    } else if (linha[0] == 'd') {
      sscanf(linha, "%*s %[^0-9] %d %[^0-9] %d", nome, &creditos, professor, &codigo);
      nome[strlen(nome)-1] = '\0';
      professor[strlen(professor)-1] = '\0';
      criar_disciplina(&ptr_i_disciplina, nome, professor, creditos, codigo);
    }
  }
  return;
}

int verificar_cpf(char*ptr){
  int i, erro1=0, erro2=0, erro3=0;
	int k=0;
	erro1=0;
	erro2=0;
	erro3=0;
	while(!erro3)
	{
		if(ptr[k]=='\0')
		{
			if(k!=12)
			{
				erro3++;	
			}
			else
				break;
		}
		else
			k++;
	}
	for(i=0;i<12;i++)
	{
		if(i==9){
			if(ptr[i]!='-' && erro3==0)
			{
				printf("CPF inserido possui formato inválido\n");
				erro2=1;
			}
		}
		else{
				int aux,zero;
				aux=(int)ptr[i];
				zero=(int)'0';
				if((aux-zero>9)||(aux-zero<0))
					erro1++;		
		}	
	}
	if(erro1==0 && erro2==0 && erro3==0)
  {
    printf("Seu cpf foi cadastrado com sucesso\n");
    return 0;
  }
	if(erro1&&erro3==0)
  {
    printf("Seu CPF deve conter apenas dígitos\n");
    return 1;
  }
	if(erro3){
		printf("Quantidade de dígitos incorreta\n");
    return 1;
	}
  return 0;
}

int verificar_periodo(int periodo){
  if(
    ((periodo%10) != 1 && (periodo%10) != 2) ||
    periodo < 19700   ||
    periodo > 20241
  ){
    p("período inválido\n");
    return 1;
  }
  return 0;
}

int verificar_codigo_disciplina(int codigo){
  if(codigo > 9999){
    p("código inválido\n");
    return 1;
  }
  return 0;
}

int verificar_codigo_aluno(int codigo){
  if(codigo > 99999){
    p("código inválido\n");
    return 1;
  }
  return 0;
}

int buscar_aluno(int codigo, Aluno **ptr){
  Aluno *ptr_aux = *ptr;
  while(ptr_aux){
    if(ptr_aux->codigo == codigo){
      return 1;
    }else if(ptr_aux->codigo > codigo){
      p("aluno não encontrado\n");
      return 0;
    }
    ptr_aux = ptr_aux->prox;
  }
  return 0;
  p("aluno não encontrado\n");
}

int buscar_disciplina(int codigo, Disciplina **ptr){
  Disciplina *ptr_aux = *ptr;
  while(ptr_aux){
    if(ptr_aux->codigo == codigo){
      return 1;
    }else if(ptr_aux->codigo > codigo){
      p("disciplina não encontrada\n");  
      return 0;
    }
    ptr_aux = ptr_aux->prox;
  }
  return 0;
  p("disciplina não encontrada\n");  
}