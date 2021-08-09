FILE *f;

struct funcionario {

    char cod[10];
    char nome[100];
    char rg[11];
    char cpf[11];
    float salario;
    char rua[50];
    char bairro[50];
    char numero[10];


    int dia;
    int mes;
    int ano;

    char tipo_sanguineo[4];

    int numero_de_dependentes;
    float salario_total;
};


struct funcionario funcionarios;

struct funcionario ordenar[50];

int verificar_arquivo();

int verificar_espacovazio(struct funcionario funcionarios);

void opcoes();

void opcoes_funcionario();

void novo_funcionario(struct funcionario funcionarios);

void inserir_codfuncionario(struct funcionario funcionarios, char *c);

void inserir_nomefuncionario(char *n);

void inserir_rgfuncionario(char *r);

void inserir_cpffuncionario(struct funcionario funcionarios, char *cpf);

void inserir_salariofuncionario(float *s);

void inserir_endefuncionario(char *rua, char *bairro, char *numero);

void inserir_datafuncionario(int *dia, int *mes, int *ano);

void inserir_tiposan_funcionario(char *t);

void alterar_funcionario(struct funcionario funcionarios);

void excluir_funcionario(struct funcionario funcionarios);

void dados_codfuncionario(struct funcionario funcionarios);

void todos_funcionario(struct funcionario funcionarios);

void ordem_funcionario(struct funcionario ordenar[], struct funcionario funcionarios);
