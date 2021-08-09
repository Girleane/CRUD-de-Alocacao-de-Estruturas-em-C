#include <stdio.h>
#include <string.h>

#include "funcionarios.h"
#include "dependentes.h"

void opcoes_dependente() {
    printf("\n1 - Inserir um novo dependente.\n");
    printf("2 - Alterar um dependente existente.\n");
    printf("3 - Excluir um dependente.\n");
    printf("4 - Mostrar dados de um dependente com base no codigo.\n");
    printf("5 - Mostrar todos os dependentes de um funcionario.\n");
    printf("6 - Mostrar todos os dependentes de um funcionario em ordem alfabetica pelo nome.\n");
    printf("0 - Menu anterior.\n");
}

int verificar_arquivod() {
    fseek(d, 0, SEEK_END);

    long tamanho = ftell(d);

    int numero_leituras = 0;
    fseek(d, 0, SEEK_SET);

    while (!feof(d)) {
        fread(&dependentes, sizeof(struct dependente), 1, d);

        if (feof(d) == 0) {
            if (strcmp(dependentes.cod, "") == 0) {
                numero_leituras++;
            }
        }
    }

    if (tamanho > 0 || numero_leituras > 0) {
        return 1;
    } else {
        return 0;
    }
}

int verificar_espacovaziod(struct dependente dependentes) {
    int numero_leituras = 0;
    fseek(d, 0, SEEK_SET);

    while (!feof(d)) {
        fread(&dependentes, sizeof(struct dependente), 1, d);

        if (feof(d) == 0) {
            if (strcmp(dependentes.cod, "") == 0) {
                return numero_leituras;
            } else {
                numero_leituras++;
            }
        }
    }
    return 0;
}

void novo_dependente(struct dependente dependentes) {
    int verificar = verificar_arquivo();

    if (verificar == 0) {
        printf("Nenhum funcinario cadastrado.\n\n");
    } else {

        printf("Digite o codigo do funcionario:\n");
        verificar_codfuncionario(funcionarios, (dependentes.cod_funcionario));

        int numero_de_dependentes = 0;
        char aux[10];
        strcpy(aux, dependentes.cod_funcionario);


        fseek(d, 0, SEEK_SET);
        while (!feof(d)) {
            fread(&dependentes, sizeof(struct dependente), 1, d);

            if (feof(d) == 0)
                if (strcmp(aux, dependentes.cod_funcionario) == 0) {
                    numero_de_dependentes++;
                }
        }

        if (numero_de_dependentes < 3) {
            printf("Digite o codigo do dependente:\n");
            inserir_coddependente(dependentes, (dependentes.cod));

            printf("Digite o nome do dependente:\n");
            inserir_nomedependente(dependentes.nome);

            printf("Digite o RG do dependente (opcional):\n");
            inserir_rgdependente(dependentes.rg);

            printf("Digite o CPF do dependente:\n");
            inserir_cpfdependente(dependentes, (dependentes.cpf));

            printf("Digite o ajuda custo do dependente:\n");
            inserir_ajuda_custodependente(&dependentes.ajuda_custo);

            printf("Digite o endereco do dependentes (opcional):\n");
            inserir_endedependente(dependentes.rua, dependentes.bairro, dependentes.numero);

            printf("Digite a data de nascimento do dependente:\n");
            inserir_datadependente(&dependentes.dia, &dependentes.mes, &dependentes.ano);

            printf("Digite o tipo sanguineo do dependente (opcional):\n");
            inserir_tiposan_dependente(dependentes.tipo_sanguineo);

            strcpy(dependentes.cod_funcionario, aux);

            printf("dependente cadrastrado com sucesso!\n\n");

            int verificar = verificar_espacovaziod(dependentes);

            if (verificar == 0) {
                fseek(d, 0, SEEK_END);
                fwrite(&dependentes, sizeof(struct dependente), 1, d);
            } else {
                fseek(d, verificar * sizeof(struct dependente), SEEK_SET);
                fwrite(&dependentes, sizeof(struct dependente), 1, d);
            }
        } else {
            printf("Quantidade maxima de dependentes atingida para esse funcionario.\n");
        }
    }
}

void verificar_codfuncionario(struct funcionario funcionarios, char *cf) {
    int cont = 0;
    int numero_leituras = 0;

    do {
        fflush(stdin);
        gets(cf);

        if (strcmp(cf, "") == 0) {
            printf("Campo obrigatorio, digite novamente.\n");
        } else {
            fseek(f, 0, SEEK_SET);
            while (!feof(f)) {
                fread(&funcionarios, sizeof(struct funcionario), 1, f);
                numero_leituras++;

                if (strcmp(cf, funcionarios.cod) == 0) {
                    break;
                } else {
                    cont++;
                }
            }
            if (cont == numero_leituras) {
                printf("Codigo de funcionario inexistente, digite novamente.\n");
                strcpy(cf, "");
            }
        }
    } while (strcmp(cf, "") == 0);
}

void inserir_coddependente(struct dependente dependentes, char *c) {

    do {
        fflush(stdin);
        gets(c);

        if (strcmp(c, "") == 0) {
            printf("Campo obrigatorio, digite novamente.\n");
        } else {
            fseek(d, 0, SEEK_SET);
            while (!feof(d)) {
                fread(&dependentes, sizeof(struct dependente), 1, d);

                if (strcmp(c, dependentes.cod) == 0) {
                    printf("Codigo ja existente, digite novamente.\n");
                    strcpy(c, "");
                    break;
                }
            }
        }
    } while (strcmp(c, "") == 0);


    printf("Codigo registrado com sucesso!\n\n");
}

void inserir_nomedependente(char *n) {
    do {
        fflush(stdin);
        gets(n);

        if (strcmp(n, "") == 0) {
            printf("Campo obrigatorio,  digite novamente:\n");
        }
    } while (strcmp(n, "") == 0);

    printf("Nome registrado com sucesso!\n\n");
}


void inserir_rgdependente(char *r) {
    fflush(stdin);
    gets(r);

    if (strcmp(r, "") != 0) {
        printf("RG registrado com sucesso!\n\n");
    }
}

void inserir_cpfdependente(struct dependente dependentes, char *cpf) {
    do {
        fflush(stdin);
        gets(cpf);

        if (strcmp(cpf, "") == 0) {
            printf("Campo obrigatorio, digite novamente.\n");
        } else {
            fseek(d, 0, SEEK_SET);
            while (!feof(d)) {
                fread(&dependentes, sizeof(struct dependente), 1, d);

                if (strcmp(cpf, dependentes.cpf) == 0) {
                    printf("Codigo ja existente, digite novamente.\n");
                    strcpy(cpf, "");
                    break;
                }
            }
        }
    } while (strcmp(cpf, "") == 0);

    printf("Codigo registrado com sucesso!\n\n");
}

void inserir_ajuda_custodependente(float *s) {
    do {
        fflush(stdin);
        scanf("%f", s);
        if (s == 0) {
            printf("Campo obrigatorio, digite novamente:\n");
        }
    } while (s == 0);

    printf("Salario registrado com sucesso!\n\n");
}

void inserir_endedependente(char *rua, char *bairro, char *numero) {
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

void inserir_datadependente(int *dia, int *mes, int *ano) {
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

void inserir_tiposan_dependente(char *t) {
    fflush(stdin);
    gets(t);

    if (strcmp(t, "") != 0) {
        printf("Tipo Sanguineo registrado com sucesso!\n\n");
    }
}

void excluir_dependente(struct dependente dependentes) {
    char aux[10];
    int verificar = verificar_arquivod();

    if (verificar == 0) {
        printf("Nenhum dependente cadastrado.\n\n");
    } else {
        printf("Digite o codigo do dependente que deseja excluir:\n");
        fflush(stdin);
        gets(aux);

        fseek(d, 0, SEEK_SET);
        while (!feof(d)) {
            fread(&dependentes, sizeof(struct dependente), 1, d);

            if (strcmp(aux, dependentes.cod) == 0) {


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

                printf("dependente excluido com sucesso!\n\n");
                break;
            }
        }
    }
}

void alterar_dependente(struct dependente dependentes) {
    char aux[10];
    int verificard = verificar_arquivod();
    int verificar = verificar_arquivo();
    int posicao = 0;

    if (verificard == 0) {
        printf("Nenhum dependente cadastrado.\n\n");
    } else if (verificar == 0) {
        printf("Nenhum funcionario cadastrado.\n\n");

    } else {
        printf("Digite o codigo do dependente que deseja altera:\n");
        fflush(stdin);
        gets(aux);

        fseek(d, 0, SEEK_SET);

        while (!feof(d)) {
            fread(&dependentes, sizeof(struct dependente), 1, d);
            posicao++;

            if (strcmp(aux, dependentes.cod) == 0) {
                printf("Digite o novo nome do dependente:\n");
                inserir_nomedependente(dependentes.nome);

                printf("Digite o novo RG do dependente: (opcional):\n");
                inserir_rgdependente(dependentes.rg);

                printf("Digite o novo CPF do dependente:\n");
                inserir_cpfdependente(dependentes, (dependentes.cpf));

                fseek(d, posicao * sizeof(struct dependente), SEEK_SET);

                printf("Digite a nova ajuda custo do dependente:\n");
                inserir_ajuda_custodependente(&dependentes.ajuda_custo);

                printf("Digite o novo endereco do dependente (opcional):\n");
                inserir_endedependente(dependentes.rua, dependentes.bairro, dependentes.numero);

                printf("Digite a nova data de nascimento do dependente:\n");
                inserir_datadependente(&dependentes.dia, &dependentes.mes, &dependentes.ano);

                printf("Digite o novo tipo sanguineo do dependente (opcional):\n");
                inserir_tiposan_dependente(dependentes.tipo_sanguineo);

                fseek(d, -1 * sizeof(struct dependente), SEEK_CUR);
                fwrite(&dependentes, sizeof(struct dependente), 1, d);

                break;
            }
        }
    }
}


void dados_coddependente(struct dependente dependentes) {
    char aux[10];
    int verificar = verificar_arquivod();

    if (verificar == 0) {
        printf("Nenhum dependente cadastrado.\n\n");
    } else {
        printf("Digite o codigo do dependente:\n");
        fflush(stdin);
        gets(aux);

        fseek(d, 0, SEEK_SET);
        while (!feof(d)) {
            fread(&dependentes, sizeof(struct dependente), 1, d);

            if (feof(d) == 0) {
                if (strcmp(aux, dependentes.cod) == 0) {
                    printf("\nCodigo do dependente: %s\n", dependentes.cod);
                    printf("Codigo do funcionario: %s\n", dependentes.cod_funcionario);
                    printf("Nome: %s\n", dependentes.nome);

                    if (strcmp(dependentes.rg, "") == 0) {
                        printf("RG: nao informado\n");
                    } else {
                        printf("RG: %s\n", dependentes.rg);
                    }

                    printf("CPF: %s\n", dependentes.cpf);
                    printf("Salario: R$%.2f\n", dependentes.ajuda_custo);

                    if (strcmp(dependentes.rua, "") == 0) {
                        printf("Endereco: nao informado\n");
                    } else {
                        printf("Endereco:\n");
                        printf("Rua: %s\n", dependentes.rua);
                        printf("Numero: %s\n", dependentes.numero);
                        printf("Bairro: %s\n", dependentes.bairro);
                    }

                    printf("Data de Nascimento: %d/%d/%d\n", dependentes.dia, dependentes.mes, dependentes.ano);

                    if (strcmp(dependentes.tipo_sanguineo, "") == 0) {
                        printf("Tipo Sanguineo: nao informado\n");
                    } else {
                        printf("Tipo Sanguineo: %s\n", dependentes.tipo_sanguineo);
                    }
                    break;
                }
            }
        }
    }
}

void todos_dependente(struct dependente dependentes) {
    char aux[10];
    int verificar = verificar_arquivo();
    int verificard = verificar_arquivod();

    if (verificar == 0) {
        printf("Nenhum funcinario cadastrado.\n\n");
    } else {
        if (verificard == 0) {
            printf("Nenhum dependente cadastrado.\n\n");
        } else {

            printf("Digite o codigo do funcionario:\n");
            verificar_codfuncionario(funcionarios, aux);

            fseek(d, 0, SEEK_SET);
            while (!feof(d)) {
                fread(&dependentes, sizeof(struct dependente), 1, d);

                if (feof(d) == 0) {
                    if (strcmp(aux, dependentes.cod_funcionario) == 0)
                        if ((strcmp(dependentes.cod, "") != 0) && (strcmp(dependentes.cpf, "") != 0)) {

                            printf("\nCodigo do dependente: %s\n", dependentes.cod);
                            printf("Codigo do funcionario: %s\n", dependentes.cod_funcionario);
                            printf("Nome: %s\n", dependentes.nome);

                            if (strcmp(dependentes.rg, "") == 0) {
                                printf("RG: nao informado\n");
                            } else {
                                printf("RG: %s\n", dependentes.rg);
                            }

                            printf("CPF: %s\n", dependentes.cpf);
                            printf("Ajuda de custo: R$%.2f\n", dependentes.ajuda_custo);

                            if (strcmp(dependentes.rua, "") == 0) {
                                printf("Endereco: nao informado\n");
                            } else {
                                printf("Endereco:\n");
                                printf("Rua: %s\n", dependentes.rua);
                                printf("Numero: %s\n", dependentes.numero);
                                printf("Bairro: %s\n", dependentes.bairro);
                            }

                            printf("Data de Nascimento: %d/%d/%d\n", dependentes.dia, dependentes.mes, dependentes.ano);

                            if (strcmp(dependentes.tipo_sanguineo, "") == 0) {
                                printf("Tipo Sanguineo: nao informado\n");
                            } else {
                                printf("Tipo Sanguineo: %s\n", dependentes.tipo_sanguineo);
                            }
                        }
                }
            }
        }
    }
}

void ordem_dependente(struct dependente ordenard[3], struct dependente dependentes) {

    int cont = 0;

    char aux_cod[10];
    int verificar = verificar_arquivo();
    int verificard = verificar_arquivod();

    if (verificar == 0) {
        printf("Nenhum funcinario cadastrado.\n\n");
    } else {
        if (verificard == 0) {
            printf("Nenhum dependente cadastrado.\n\n");
        } else {
            printf("Digite o codigo do funcionario:\n");
            verificar_codfuncionario(funcionarios, aux_cod);

            fseek(d, 0, SEEK_SET);
            while (!feof(d)) {
                fread(&dependentes, sizeof(struct dependente), 1, d);

                if (feof(d) == 0) {
                    if (strcmp(aux_cod, dependentes.cod_funcionario) == 0)
                        strcpy(ordenard[cont].cod, dependentes.cod);
                    strcpy(ordenard[cont].cod, dependentes.cod);
                    strcpy(ordenard[cont].nome, dependentes.nome);
                    strcpy(ordenard[cont].rg, dependentes.rg);
                    strcpy(ordenard[cont].cpf, dependentes.cpf);
                    ordenard[cont].ajuda_custo = dependentes.ajuda_custo;

                    strcpy(ordenard[cont].rua, dependentes.rua);
                    strcpy(ordenard[cont].bairro, dependentes.bairro);
                    strcpy(ordenard[cont].numero, dependentes.numero);

                    ordenard[cont].dia = dependentes.dia;
                    ordenard[cont].mes = dependentes.mes;
                    ordenard[cont].ano = dependentes.ano;

                    strcpy(ordenard[cont].tipo_sanguineo, dependentes.tipo_sanguineo);
                    cont++;
                }

            }

            char aux[100];
            int aux_num;
            float aux_float;

            for (int i = 0; i < cont; i++) {
                for (int j = 1; j < cont; j++) {
                    if (strcmp(ordenard[j - 1].nome, ordenard[j].nome) > 0) {
                        strcpy(aux, ordenard[j - 1].cod);
                        strcpy(ordenard[j - 1].cod, ordenard[j].cod);
                        strcpy(ordenard[j].cod, aux);

                        strcpy(aux, ordenard[j - 1].nome);
                        strcpy(ordenard[j - 1].nome, ordenard[j].nome);
                        strcpy(ordenard[j].nome, aux);

                        strcpy(aux, ordenard[j - 1].rg);
                        strcpy(ordenard[j - 1].rg, ordenard[j].rg);
                        strcpy(ordenard[j].rg, aux);

                        strcpy(aux, ordenard[j - 1].cpf);
                        strcpy(ordenard[j - 1].cpf, ordenard[j].cpf);
                        strcpy(ordenard[j].cpf, aux);

                        aux_float = ordenard[j - 1].ajuda_custo;
                        ordenard[j - 1].ajuda_custo = ordenard[j].ajuda_custo;
                        ordenard[j].ajuda_custo = aux_float;

                        strcpy(aux, ordenard[j - 1].rua);
                        strcpy(ordenard[j - 1].rua, ordenard[j].rua);
                        strcpy(ordenard[j].rua, aux);

                        strcpy(aux, ordenard[j - 1].bairro);
                        strcpy(ordenard[j - 1].bairro, ordenard[j].bairro);
                        strcpy(ordenard[j].bairro, aux);

                        strcpy(aux, ordenard[j - 1].numero);
                        strcpy(ordenard[j - 1].numero, ordenard[j].numero);
                        strcpy(ordenard[j].numero, aux);

                        aux_num = ordenard[j - 1].dia;
                        ordenard[j - 1].dia = ordenard[j].dia;
                        ordenard[j].dia = aux_num;

                        aux_num = ordenard[j - 1].mes;
                        ordenard[j - 1].mes = ordenard[j].mes;
                        ordenard[j].mes = aux_num;

                        aux_num = ordenard[j - 1].ano;
                        ordenard[j - 1].ano = ordenard[j].ano;
                        ordenard[j].ano = aux_num;

                        strcpy(aux, ordenard[j - 1].tipo_sanguineo);
                        strcpy(ordenard[j - 1].tipo_sanguineo, ordenard[j].tipo_sanguineo);
                        strcpy(ordenard[j].tipo_sanguineo, aux);
                    }
                }
            }

            for (int i = 0; i < cont; i++) {
                if (strcmp(ordenard[i].nome, "") != 0) {
                    printf("\nNome: %s\n", ordenard[i].nome);

                    printf("Codigo: %s\n", ordenard[i].cod);
                    if (strcmp(ordenard[i].rg, "") == 0) {
                        printf("RG: nao informado\n");
                    } else {
                        printf("RG: %s\n", ordenard[i].rg);
                    }

                    printf("CPF: %s\n", ordenard[i].cpf);
                    printf("ajuda_custo: R$%.2f\n", ordenard[i].ajuda_custo);

                    if (strcmp(ordenard[i].rua, "") == 0) {
                        printf("Endereco: nao informado\n");
                    } else {
                        printf("Endereco:\n");
                        printf("Rua: %s\n", ordenard[i].rua);
                        printf("Numero: %s\n", ordenard[i].numero);
                        printf("Bairro: %s\n", ordenard[i].bairro);
                    }

                    printf("Data de Nascimento: %d/%d/%d\n", ordenard[i].dia, ordenard[i].mes, ordenard[i].ano);

                    if (strcmp(ordenard[i].tipo_sanguineo, "") == 0) {
                        printf("Tipo Sanguineo: nao informado\n");
                    } else {
                        printf("Tipo Sanguineo: %s\n", ordenard[i].tipo_sanguineo);
                    }
                }
            }
        }
    }
}