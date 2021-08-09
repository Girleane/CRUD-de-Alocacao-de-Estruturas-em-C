#include <stdio.h>

#include "funcionarios.h"
#include "dependentes.h"

int main() {
    f = fopen("funcionario.bin", "rb+");
    d = fopen("dependente.bin", "rb+");

    if (f == NULL) {
        f = fopen("funcionario.bin", "wb+");
       // printf("Novo arquivo funcionario\n");
    }

    if (d == NULL) {
        d = fopen("dependente.bin", "wb+");
     //   printf("Novo arquivo dependente\n");
    }

    int opf, opd, opcao;

    do {
        opcoes();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                do {
                    opcoes_funcionario();
                    scanf("%d", &opf);

                    switch (opf) {
                        case 1:
                            novo_funcionario(funcionarios);
                            break;
                        case 2:
                            alterar_funcionario(funcionarios);
                            break;
                        case 3:
                            excluir_funcionario(funcionarios);
                            break;
                        case 4:
                            dados_codfuncionario(funcionarios);
                            break;
                        case 5:
                            todos_funcionario(funcionarios);
                            break;

                        case 6:
                            ordem_funcionario(ordenar, funcionarios);
                            break;
                        case 0:
                            break;

                        default:
                            printf("Opcao invalida, digite novamente:\n");
                            break;
                    }
                } while (opf != 0);
                break;

            case 2:
                do {
                    opcoes_dependente();
                    scanf("%d", &opd);

                    switch (opd) {
                        case 1:
                            novo_dependente(dependentes);
                            break;

                        case 2:
                            alterar_dependente(dependentes);
                            break;

                        case 3:
                            excluir_dependente(dependentes);
                            break;

                        case 4:
                            dados_coddependente(dependentes);
                            break;

                        case 5:
                            todos_dependente(dependentes);
                            break;
                        case 6:
                            ordem_dependente(ordenard, dependentes);
                            break;

                        case 0:
                            break;

                        default:
                            printf("Opcao invalida, digite novamente:\n");
                            break;
                    }
                } while (opd != 0);
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida, digite novamente:\n");
                break;
        }
    } while (opcao != 0);


    fclose(f);
    return 0;
}

