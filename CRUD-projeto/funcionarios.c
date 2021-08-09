#include <stdio.h>
#include <string.h>

#include "funcionarios.h"
#include "dependentes.h"

void opcoes() {
    printf("Digite uma opcao:\n");
    printf("\n1 - Funcionario\n");
    printf("2 - Dependente\n");
    printf("0 - Sair\n");
}

void opcoes_funcionario() {
    printf("\n1 - Inserir um novo funcionario.\n");
    printf("2 - Alterar um funcionario existente.\n");
    printf("3 - Excluir um funcionario.\n");
    printf("4 - Mostrar dados de um funcionario com base no codigo.\n");
    printf("5 - Mostrar todos os funcionarios.\n");
    printf("6 - Mostrar todos os funcionarios em ordem alfabetica pelo nome.\n");
    printf("0 - Menu anterior.\n");
}

int verificar_arquivo() {
    fseek(f, 0, SEEK_END);

    long tamanho = ftell(f);
    int vazio = 0;
    int numero_leituras = 0;

    fseek(f, 0, SEEK_SET);

    while (!feof(f)) {
        fread(&funcionarios, sizeof(struct funcionario), 1, f);

        if (feof(f) == 0) {
            numero_leituras++;
            if (strcmp(funcionarios.cod, "") == 0) {
                vazio++;
            }
        }
    }

    if (numero_leituras == 1 && vazio == numero_leituras) {
        return 0;
    } else if (tamanho > 0) {
        return 1;
    } else {
        return 0;
    }
}

int verificar_espacovazio(struct funcionario funcionarios) {
    fseek(f, 0, SEEK_SET);

    while (!feof(f)) {
        fread(&funcionarios, sizeof(struct funcionario), 1, f);

        if (feof(f) == 0) {
            if (strcmp(funcionarios.cod, "") == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void novo_funcionario(struct funcionario funcionarios) {
    printf("Digite o codigo do funcionario:\n");
    inserir_codfuncionario(funcionarios, (funcionarios.cod));

    printf("Digite o nome do funcionario:\n");
    inserir_nomefuncionario(funcionarios.nome);

    printf("Digite o RG do funcionario (opcional):\n");
    inserir_rgfuncionario(funcionarios.rg);

    printf("Digite o CPF do funcionario:\n");
    inserir_cpffuncionario(funcionarios, (funcionarios.cpf));

    printf("Digite o salario do funcionario:\n");
    inserir_salariofuncionario(&funcionarios.salario);

    printf("Digite o endereco do funcionario (opcional):\n");
    inserir_endefuncionario(funcionarios.rua, funcionarios.bairro, funcionarios.numero);

    printf("Digite a data de nascimento do funcionario:\n");
    inserir_datafuncionario(&funcionarios.dia, &funcionarios.mes, &funcionarios.ano);

    printf("Digite o tipo sanguineo do funcionario (opcional):\n");
    inserir_tiposan_funcionario(funcionarios.tipo_sanguineo);

    printf("Funcionario cadrastrado com sucesso!\n\n");

    int verificar = verificar_espacovazio(funcionarios);

    if (verificar == 0) {
        fseek(f, 0, SEEK_END);
        fwrite(&funcionarios, sizeof(struct funcionario), 1, f);
    } else {
        fseek(f, -1 * sizeof(struct funcionario), SEEK_CUR);
        fwrite(&funcionarios, sizeof(struct funcionario), 1, f);
    }
}

void inserir_codfuncionario(struct funcionario funcionarios, char *c) {
    do {
        fflush(stdin);
        gets(c);

        if (strcmp(c, "") == 0) {
            printf("Campo obrigatorio, digite novamente.\n");
        } else {
            fseek(f, 0, SEEK_SET);
            while (!feof(f)) {
                fread(&funcionarios, sizeof(struct funcionario), 1, f);

                if (strcmp(c, funcionarios.cod) == 0) {
                    printf("Codigo ja existente, digite novamente.\n");
                    strcpy(c, "");
                    break;
                }
            }
        }
    } while (strcmp(c, "") == 0);

    printf("Codigo registrado com sucesso!\n\n");
}

void inserir_nomefuncionario(char *n) {
    do {
        fflush(stdin);
        gets(n);

        if (strcmp(n, "") == 0) {
            printf("Campo obrigatorio,  digite novamente:\n");
        }
    } while (strcmp(n, "") == 0);

    printf("Nome registrado com sucesso!\n\n");
}

void inserir_rgfuncionario(char *r) {
    fflush(stdin);
    gets(r);

    if (strcmp(r, "") != 0) {
        printf("RG registrado com sucesso!\n\n");
    }
}

void inserir_cpffuncionario(struct funcionario funcionarios, char *cpf) {
    do {
        fflush(stdin);
        gets(cpf);

        if (strcmp(cpf, "") == 0) {
            printf("Campo obrigatorio, digite novamente.\n");
        } else {
            fseek(f, 0, SEEK_SET);
            while (!feof(f)) {
                fread(&funcionarios, sizeof(struct funcionario), 1, f);

                if (strcmp(cpf, funcionarios.cpf) == 0) {
                    printf("Codigo ja existente, digite novamente.\n");
                    strcpy(cpf, "");
                    break;
                }
            }
        }
    } while (strcmp(cpf, "") == 0);

    printf("Codigo registrado com sucesso!\n\n");
}

void inserir_salariofuncionario(float *s) {
    do {
        fflush(stdin);
        scanf("%f", s);

        if (s == 0) {
            printf("Campo obrigatorio,  digite novamente:\n");
        }
    } while (s == 0);

    printf("Salario registrado com sucesso!\n\n");
}

void inserir_endefuncionario(char *rua, char *bairro, char *numero) {
    printf("Insira o nome da rua: \n");
    fflush(stdin);
    gets(rua);

    printf("\nInsira o nome bairro: \n");
    fflush(stdin);
    gets(bairro);

    printf("\nInsira o numero da sua casa: \n");
    gets(numero);

    if (strcmp(rua, "") != 0) {
        printf("\nEndereco adicionado com sucesso!\n\n");
    }
}

void inserir_datafuncionario(int *dia, int *mes, int *ano) {
    do {
        printf("Dia:");
        scanf("%d", dia);

        printf("Mes:");
        scanf("%d", mes);

        printf("Ano:");
        scanf("%d", ano);

        if ((*dia <= 0) || (*dia > 31)) {
            *dia = 0;
        }

        if ((*mes <= 0) || (*mes > 12)) {
            *mes = 0;
        }

        if ((*ano <= 0)) {
            *ano = 0;
        }

        if ((*dia == 0) || (*mes == 0) || (*ano == 0)) {
            printf("Data invalida, digite novamente.\n");
        }

    } while ((*dia == 0) || (*mes == 0) || (*ano == 0));

    printf("Data de nascimento registrada com sucesso!\n\n");
}

void inserir_tiposan_funcionario(char *t) {
    fflush(stdin);
    gets(t);

    if (strcmp(t, "") != 0) {
        printf("Tipo Sanguineo registrado com sucesso!\n\n");
    }
}

void alterar_funcionario(struct funcionario funcionarios) {
    char aux[10];
    int verificar = verificar_arquivo();
    int posicao = 0;

    if (verificar == 0) {
        printf("Nenhum funcinario cadastrado.\n\n");
    } else {
        printf("Digite o codigo do funcionario que deseja altera:\n");
        fflush(stdin);
        gets(aux);

        fseek(f, 0, SEEK_SET);

        while (!feof(f)) {
            fread(&funcionarios, sizeof(struct funcionario), 1, f);
            posicao++;

            if (strcmp(aux, funcionarios.cod) == 0) {
                printf("Digite o novo nome do funcionario:\n");
                inserir_nomefuncionario(funcionarios.nome);

                printf("Digite o novo RG do funcionario (opcional):\n");
                inserir_rgfuncionario(funcionarios.rg);

                printf("Digite o novo CPF do funcionario:\n");
                inserir_cpffuncionario(funcionarios, (funcionarios.cpf));

                fseek(f, posicao * sizeof(struct funcionario), SEEK_SET);

                printf("Digite o novo salario do funcionario:\n");
                inserir_salariofuncionario(&funcionarios.salario);

                printf("Digite o novo endereco do funcionario (opcional):\n");
                inserir_endefuncionario(funcionarios.rua, funcionarios.bairro, funcionarios.numero);

                printf("Digite a nova data de nascimento do funcionario:\n");
                inserir_datafuncionario(&funcionarios.dia, &funcionarios.mes, &funcionarios.ano);

                printf("Digite o novo tipo sanguineo do funcionario (opcional):\n");
                inserir_tiposan_funcionario(funcionarios.tipo_sanguineo);

                fseek(f, -1 * sizeof(struct funcionario), SEEK_CUR);
                fwrite(&funcionarios, sizeof(struct funcionario), 1, f);

                break;
            }
        }
    }
}

void excluir_funcionario(struct funcionario funcionarios) {
    char aux[10];
    int verificar = verificar_arquivo();

    if (verificar == 0) {
        printf("Nenhum funcinario cadastrado.\n\n");
    } else {
        printf("Digite o codigo do funcionario que deseja excluir:\n");
        fflush(stdin);
        gets(aux);

        fseek(f, 0, SEEK_SET);
        while (!feof(f)) {
            fread(&funcionarios, sizeof(struct funcionario), 1, f);

            if (strcmp(aux, funcionarios.cod) == 0) {

                strcpy(funcionarios.cod, "");
                strcpy(funcionarios.nome, "");
                strcpy(funcionarios.rg, "");
                strcpy(funcionarios.cpf, "");
                funcionarios.salario = 0;

                strcpy(funcionarios.rua, "");
                strcpy(funcionarios.bairro, "");
                strcpy(funcionarios.numero, "");

                funcionarios.dia = 0;
                funcionarios.mes = 0;
                funcionarios.ano = 0;

                strcpy(funcionarios.tipo_sanguineo, "");

                fseek(f, -1 * sizeof(struct funcionario), SEEK_CUR);
                fwrite(&funcionarios, sizeof(struct funcionario), 1, f);

                printf("Funcionario excluido com sucesso!\n\n");
                break;
            }
        }
        fseek(d, 0, SEEK_SET);
        while (!feof(d)) {
            fread(&dependentes, sizeof(struct dependente), 1, d);
            if (strcmp(dependentes.cod_funcionario, aux) == 0) {
                strcpy(dependentes.cod, "");
                strcpy(dependentes.nome, "");
                strcpy(dependentes.rg, "");
                strcpy(dependentes.cpf, "");
                dependentes.ajuda_custo = 0;

                strcpy(dependentes.rua, "");
                strcpy(dependentes.bairro, "");
                strcpy(dependentes.numero, "");

                dependentes.dia = 0;
                dependentes.mes = 0;
                dependentes.ano = 0;

                strcpy(dependentes.tipo_sanguineo, "");
                strcpy(dependentes.cod_funcionario, "");
                fseek(d, -1 * sizeof(struct dependente), SEEK_CUR);
                fwrite(&dependentes, sizeof(struct dependente), 1, d);
            }
        }
    }
}

void dados_codfuncionario(struct funcionario funcionarios) {
    char aux[10];
    int verificar = verificar_arquivo();

    if (verificar == 0) {
        printf("Nenhum funcinario cadastrado.\n\n");
    } else {
        printf("Digite o codigo do funcionario:\n");
        fflush(stdin);
        gets(aux);

        fseek(f, 0, SEEK_SET);
        while (!feof(f)) {
            fread(&funcionarios, sizeof(struct funcionario), 1, f);

            if (feof(f) == 0) {
                if (strcmp(aux, funcionarios.cod) == 0) {
                    printf("\nCodigo: %s\n", funcionarios.cod);
                    printf("Nome: %s\n", funcionarios.nome);

                    if (strcmp(funcionarios.rg, "") == 0) {
                        printf("RG: nao informado\n");
                    } else {
                        printf("RG: %s\n", funcionarios.rg);
                    }

                    printf("CPF: %s\n", funcionarios.cpf);
                    printf("Salario: R$%.2f\n", funcionarios.salario);

                    if (strcmp(funcionarios.rua, "") == 0) {
                        printf("Endereco: nao informado\n");
                    } else {
                        printf("Endereco:\n");
                        printf("Rua: %s\n", funcionarios.rua);
                        printf("Numero: %s\n", funcionarios.numero);
                        printf("Bairro: %s\n", funcionarios.bairro);
                    }

                    printf("Data de Nascimento: %d/%d/%d\n", funcionarios.dia, funcionarios.mes, funcionarios.ano);

                    if (strcmp(funcionarios.tipo_sanguineo, "") == 0) {
                        printf("Tipo Sanguineo: nao informado\n");
                    } else {
                        printf("Tipo Sanguineo: %s\n", funcionarios.tipo_sanguineo);
                    }

                    fseek(d, 0, SEEK_SET);
                    while (!feof(d)) {
                        fread(&dependentes, sizeof(struct dependente), 1, d);

                        if (feof(d) == 0)
                            if (strcmp(funcionarios.cod, dependentes.cod_funcionario) == 0) {
                                funcionarios.numero_de_dependentes++;
                                funcionarios.salario_total += dependentes.ajuda_custo;
                            }
                    }

                    funcionarios.salario_total += funcionarios.salario;

                    printf("Numero de dependentes: %d\n", funcionarios.numero_de_dependentes);

                    printf("Quantia total paga ao funcionario em razao dos dependentes: R$%.2f\n",
                           funcionarios.salario_total);
                    break;
                }
            }
        }
    }
}

void todos_funcionario(struct funcionario funcionarios) {

    float despesas_totais = 0;

    int verificar = verificar_arquivo();

    if (verificar == 0) {
        printf("Nenhum funcinario cadastrado.\n\n");
    } else {
        fseek(f, 0, SEEK_SET);
        while (!feof(f)) {
            fread(&funcionarios, sizeof(struct funcionario), 1, f);

            if (feof(f) == 0) {
                if ((strcmp(funcionarios.cod, "") != 0) && (strcmp(funcionarios.cpf, "") != 0)) {
                    printf("\nCodigo: %s\n", funcionarios.cod);
                    printf("Nome: %s\n", funcionarios.nome);

                    if (strcmp(funcionarios.rg, "") == 0) {
                        printf("RG: nao informado\n");
                    } else {
                        printf("RG: %s\n", funcionarios.rg);
                    }

                    printf("CPF: %s\n", funcionarios.cpf);
                    printf("Salario: R$%.2f\n", funcionarios.salario);

                    if (strcmp(funcionarios.rua, "") == 0) {
                        printf("Endereco: nao informado\n");
                    } else {
                        printf("Endereco:\n");
                        printf("Rua: %s\n", funcionarios.rua);
                        printf("Numero: %s\n", funcionarios.numero);
                        printf("Bairro: %s\n", funcionarios.bairro);
                    }

                    printf("Data de Nascimento: %d/%d/%d\n", funcionarios.dia, funcionarios.mes, funcionarios.ano);

                    if (strcmp(funcionarios.tipo_sanguineo, "") == 0) {
                        printf("Tipo Sanguineo: nao informado\n");
                    } else {
                        printf("Tipo Sanguineo: %s\n", funcionarios.tipo_sanguineo);
                    }

                    fseek(d, 0, SEEK_SET);
                    while (!feof(d)) {
                        fread(&dependentes, sizeof(struct dependente), 1, d);

                        if (feof(d) == 0)
                            if (strcmp(funcionarios.cod, dependentes.cod_funcionario) == 0) {
                                funcionarios.numero_de_dependentes++;
                                funcionarios.salario_total += dependentes.ajuda_custo;
                            }
                    }

                    funcionarios.salario_total += funcionarios.salario;

                    printf("Numero de dependentes: %d\n", funcionarios.numero_de_dependentes);

                    printf("Quantia total paga ao funcionario: R$%.2f\n", funcionarios.salario_total);

                    despesas_totais += funcionarios.salario_total;
                }

            }
        }
    }
    printf("\nDespesas totais: R$%.2f\n", despesas_totais);
}


void ordem_funcionario(struct funcionario ordenar[], struct funcionario funcionarios) {

    int cont = 0;
    int verificar = verificar_arquivo();

    if (verificar == 0) {
        printf("Nenhum funcinario cadastrado.\n\n");
    } else {
        fseek(f, 0, SEEK_SET);
        while (!feof(f)) {
            fread(&funcionarios, sizeof(struct funcionario), 1, f);

            if (feof(f) == 0) {

                fseek(d, 0, SEEK_SET);
                while (!feof(d)) {
                    fread(&dependentes, sizeof(struct dependente), 1, d);

                    if (feof(d) == 0)
                        if (strcmp(funcionarios.cod, dependentes.cod_funcionario) == 0) {
                            funcionarios.salario_total += dependentes.ajuda_custo;
                            funcionarios.numero_de_dependentes++;
                        }
                }

                funcionarios.salario_total += funcionarios.salario;

                ordenar[cont].salario_total = funcionarios.salario_total;

                ordenar[cont].numero_de_dependentes = funcionarios.numero_de_dependentes;

                strcpy(ordenar[cont].cod, funcionarios.cod);
                strcpy(ordenar[cont].cod, funcionarios.cod);
                strcpy(ordenar[cont].nome, funcionarios.nome);
                strcpy(ordenar[cont].rg, funcionarios.rg);
                strcpy(ordenar[cont].cpf, funcionarios.cpf);
                ordenar[cont].salario = funcionarios.salario;

                strcpy(ordenar[cont].rua, funcionarios.rua);
                strcpy(ordenar[cont].bairro, funcionarios.bairro);
                strcpy(ordenar[cont].numero, funcionarios.numero);

                ordenar[cont].dia = funcionarios.dia;
                ordenar[cont].mes = funcionarios.mes;
                ordenar[cont].ano = funcionarios.ano;

                strcpy(ordenar[cont].tipo_sanguineo, funcionarios.tipo_sanguineo);
                cont++;
            }

        }

        char aux[100];
        int aux_num;
        float aux_float;

        for (int i = 0; i < cont; i++) {
            for (int j = 1; j < cont; j++) {
                if (strcmp(ordenar[j - 1].nome, ordenar[j].nome) > 0) {
                    strcpy(aux, ordenar[j - 1].cod);
                    strcpy(ordenar[j - 1].cod, ordenar[j].cod);
                    strcpy(ordenar[j].cod, aux);

                    strcpy(aux, ordenar[j - 1].nome);
                    strcpy(ordenar[j - 1].nome, ordenar[j].nome);
                    strcpy(ordenar[j].nome, aux);

                    strcpy(aux, ordenar[j - 1].rg);
                    strcpy(ordenar[j - 1].rg, ordenar[j].rg);
                    strcpy(ordenar[j].rg, aux);

                    strcpy(aux, ordenar[j - 1].cpf);
                    strcpy(ordenar[j - 1].cpf, ordenar[j].cpf);
                    strcpy(ordenar[j].cpf, aux);

                    aux_float = ordenar[j - 1].salario;
                    ordenar[j - 1].salario = ordenar[j].salario;
                    ordenar[j].salario = aux_float;

                    strcpy(aux, ordenar[j - 1].rua);
                    strcpy(ordenar[j - 1].rua, ordenar[j].rua);
                    strcpy(ordenar[j].rua, aux);

                    strcpy(aux, ordenar[j - 1].bairro);
                    strcpy(ordenar[j - 1].bairro, ordenar[j].bairro);
                    strcpy(ordenar[j].bairro, aux);

                    strcpy(aux, ordenar[j - 1].numero);
                    strcpy(ordenar[j - 1].numero, ordenar[j].numero);
                    strcpy(ordenar[j].numero, aux);

                    aux_num = ordenar[j - 1].dia;
                    ordenar[j - 1].dia = ordenar[j].dia;
                    ordenar[j].dia = aux_num;

                    aux_num = ordenar[j - 1].mes;
                    ordenar[j - 1].mes = ordenar[j].mes;
                    ordenar[j].mes = aux_num;

                    aux_num = ordenar[j - 1].ano;
                    ordenar[j - 1].ano = ordenar[j].ano;
                    ordenar[j].ano = aux_num;

                    strcpy(aux, ordenar[j - 1].tipo_sanguineo);
                    strcpy(ordenar[j - 1].tipo_sanguineo, ordenar[j].tipo_sanguineo);
                    strcpy(ordenar[j].tipo_sanguineo, aux);

                    aux_float = ordenar[j - 1].salario_total;
                    ordenar[j - 1].salario_total = ordenar[j].salario_total;
                    ordenar[j].salario_total = aux_float;

                    aux_num = ordenar[j - 1].numero_de_dependentes;
                    ordenar[j - 1].numero_de_dependentes = ordenar[j].numero_de_dependentes;
                    ordenar[j].numero_de_dependentes = aux_num;
                }
            }
        }

        for (int i = 0; i < 50; i++) {
            if (strcmp(ordenar[i].nome, "") != 0) {
                printf("\nNome: %s\n", ordenar[i].nome);

                printf("Codigo: %s\n", ordenar[i].cod);
                if (strcmp(ordenar[i].rg, "") == 0) {
                    printf("RG: nao informado\n");
                } else {
                    printf("RG: %s\n", ordenar[i].rg);
                }

                printf("CPF: %s\n", ordenar[i].cpf);
                printf("Salario: R$%.2f\n", ordenar[i].salario);

                if (strcmp(ordenar[i].rua, "") == 0) {
                    printf("Endereco: nao informado\n");
                } else {
                    printf("Endereco:\n");
                    printf("Rua: %s\n", ordenar[i].rua);
                    printf("Numero: %s\n", ordenar[i].numero);
                    printf("Bairro: %s\n", ordenar[i].bairro);
                }

                printf("Data de Nascimento: %d/%d/%d\n", ordenar[i].dia, ordenar[i].mes, ordenar[i].ano);

                if (strcmp(ordenar[i].tipo_sanguineo, "") == 0) {
                    printf("Tipo Sanguineo: nao informado\n");
                } else {
                    printf("Tipo Sanguineo: %s\n", ordenar[i].tipo_sanguineo);
                }

                printf("Numero de dependentes: %d\n", ordenar[i].numero_de_dependentes);

                printf("Quantia total paga ao funcionario em razao de seus dependentes: R$%.2f\n",
                       ordenar[i].salario_total);

            }
        }
    }
}

