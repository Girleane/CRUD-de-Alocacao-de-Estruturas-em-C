
FILE *d;

struct dependente {
    char cod[10];
    char nome[100];
    char rg[11];
    char cpf[11];
    float ajuda_custo;

    char rua[50];
    char bairro[50];
    char numero[10];

    int dia;
    int mes;
    int ano;

    char tipo_sanguineo[4];

    char cod_funcionario[10];
};
struct dependente ordenard[3];
struct dependente dependentes;

void opcoes_dependente();

int verificar_arquivod();

int verificar_espacovaziod(struct dependente dependentes);


void novo_dependente(struct dependente dependentes);

void verificar_codfuncionario(struct funcionario funcionarios, char *cf);

void inserir_coddependente(struct dependente dependentes, char *c);

void inserir_nomedependente(char *n);

void inserir_rgdependente(char *r);

void inserir_cpfdependente(struct dependente dependentes, char *cpf);

void inserir_ajuda_custodependente(float *s);

void inserir_endedependente(char *rua, char *bairro, char *numero);

void inserir_datadependente(int *dia, int *mes, int *ano);

void inserir_tiposan_dependente(char *t);

void excluir_dependente(struct dependente dependentes);

void alterar_dependente(struct dependente dependentes);


void dados_coddependente(struct dependente dependentes);

void todos_dependente(struct dependente dependentes);

void ordem_dependente(struct dependente ordenard[50], struct dependente dependentes);