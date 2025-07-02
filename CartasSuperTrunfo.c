#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char estado;
    char codigo[4];
    char nome[100];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
} Carta;

int carregarCartas(Carta cartas[], const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo '%s'.\n", nomeArquivo);
        return 0;
    }

    int count = 0;
    while (fscanf(arquivo, " %c;%3[^;];%99[^;];%d;%f;%f;%d\n",
                  &cartas[count].estado,
                  cartas[count].codigo,
                  cartas[count].nome,
                  &cartas[count].populacao,
                  &cartas[count].area,
                  &cartas[count].pib,
                  &cartas[count].pontosTuristicos) == 7) {
        count++;
        if (count >= 2) break;
    }

    fclose(arquivo);
    return count;
}

void exibirCarta(Carta c) {
    printf("Estado: %c | Código: %s | Cidade: %s\n", c.estado, c.codigo, c.nome);
    printf("População: %d | Área: %.2f km² | PIB: %.2f bi | Pontos Turísticos: %d\n\n",
           c.populacao, c.area, c.pib, c.pontosTuristicos);
}

int compararAtributo(Carta c1, Carta c2, int atributo) {
    switch (atributo) {
        case 1: return (c1.populacao > c2.populacao) - (c1.populacao < c2.populacao);
        case 2: return (c1.area > c2.area) - (c1.area < c2.area);
        case 3: return (c1.pib > c2.pib) - (c1.pib < c2.pib);
        case 4: return (c1.pontosTuristicos > c2.pontosTuristicos) - (c1.pontosTuristicos < c2.pontosTuristicos);
        default: return 0;
    }
}

void jogarRodada(Carta c1, Carta c2) {
    srand(time(NULL));
    int atributo = 1 + rand() % 4;

    printf("\nAtributo sorteado: ");
    switch (atributo) {
        case 1: printf("População\n"); break;
        case 2: printf("Área\n"); break;
        case 3: printf("PIB\n"); break;
        case 4: printf("Pontos Turísticos\n"); break;
    }

    printf("\nCarta 1:\n"); exibirCarta(c1);
    printf("Carta 2:\n"); exibirCarta(c2);

    int resultado = compararAtributo(c1, c2, atributo);
    if (resultado > 0)
        printf(">> Carta 1 venceu!\n");
    else if (resultado < 0)
        printf(">> Carta 2 venceu!\n");
    else
        printf(">> Empate!\n");
}

int main() {
    Carta cartas[2];
    int carregadas = carregarCartas(cartas, "cartas.txt");

    if (carregadas < 2) {
        printf("É necessário ter 2 cartas no arquivo.\n");
        return 1;
    }

    int opcao;
    do {
        printf("\n==== SUPER TRUNFO - 2 CARTAS ====\n");
        printf("1 - Ver Cartas\n");
        printf("2 - Jogar Rodada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirCarta(cartas[0]);
                exibirCarta(cartas[1]);
                break;
            case 2:
                jogarRodada(cartas[0], cartas[1]);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
