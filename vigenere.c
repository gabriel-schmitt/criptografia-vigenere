#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_LETRAS 26
#define TAM_TEXTO 512
#define TAM_CHAVE 64

typedef struct {
  const char *texto;
  const char *chave;
  const char *esperado;
} Teste;

static const Teste TESTES[] = {
    {"ATTACKATDAWN", "LEMON", "LXFOPVEFRNHR"},
    {"Estrutura de Dados II: criptografia e legal!", "UCS", NULL},
    {"AAAAAAAAAAAAAAAA", "ABCD", NULL},
    {"ATACAR AO AMANHECER", "D", NULL},
};
#define N_TESTES (int)(sizeof(TESTES) / sizeof(TESTES[0]))

int chave_valida(const char *chave) {
  if (chave[0] == '\0') return 0;
  for (int i = 0; chave[i] != '\0'; i++)
    if (!isalpha((unsigned char)chave[i])) return 0;
  return 1;
}

/* sentido 1 cifra e -1 decifra */
void aplicar_vigenere(char *texto, const char *chave, int sentido) {
  int n = (int)strlen(chave);
  int j = 0;

  for (int i = 0; texto[i] != '\0'; i++) {
    unsigned char c = (unsigned char)texto[i];
    char base;
    int k;

    if (!isalpha(c)) continue;
    base = isupper(c) ? 'A' : 'a';
    /* j e nao i: a chave so avanca nas letras, espaco e pontuacao nao gastam chave */
    k = toupper((unsigned char)chave[j % n]) - 'A';
    /* + N_LETRAS porque em C o resto de um negativo sai negativo */
    texto[i] = (char)(base + (c - base + sentido * k + N_LETRAS) % N_LETRAS);
    j++;
  }
}

void rodar_testes(void) {
  char cifrado[TAM_TEXTO], decifrado[TAM_TEXTO];

  for (int t = 0; t < N_TESTES; t++) {
    strcpy(cifrado, TESTES[t].texto);
    aplicar_vigenere(cifrado, TESTES[t].chave, 1);
    strcpy(decifrado, cifrado);
    aplicar_vigenere(decifrado, TESTES[t].chave, -1);

    printf("\n  teste %d, chave \"%s\"\n", t + 1, TESTES[t].chave);
    printf("    original:  %s\n", TESTES[t].texto);
    printf("    cifrado:   %s\n", cifrado);
    printf("    decifrado: %s\n", decifrado);
    printf("    volta ao original: %s\n", strcmp(decifrado, TESTES[t].texto) == 0 ? "sim" : "NAO");
    if (TESTES[t].esperado != NULL)
      printf("    confere com a fonte (%s): %s\n", TESTES[t].esperado,
             strcmp(cifrado, TESTES[t].esperado) == 0 ? "sim" : "NAO");
  }
}

int ler_texto(const char *rotulo, char *destino, int tam) {
  char buffer[TAM_TEXTO];

  printf("%s", rotulo);
  fflush(stdout);
  if (fgets(buffer, sizeof(buffer), stdin) == NULL) return 0;

  buffer[strcspn(buffer, "\r\n")] = '\0';
  if (buffer[0] == '\0') return 0;

  strncpy(destino, buffer, tam - 1);
  destino[tam - 1] = '\0';
  return 1;
}

void processar_digitado(int sentido) {
  char texto[TAM_TEXTO], chave[TAM_CHAVE];

  if (!ler_texto("texto: ", texto, sizeof(texto))) return;
  if (!ler_texto("chave (so letras): ", chave, sizeof(chave)) || !chave_valida(chave)) {
    printf("  chave invalida\n");
    return;
  }

  aplicar_vigenere(texto, chave, sentido);
  printf("  %s: %s\n", sentido == 1 ? "cifrado" : "decifrado", texto);
}

/* a posicao no vetor e o numero da opcao */
static const char *OPCOES[] = {
    "sair",
    "cifrar um texto",
    "decifrar um texto",
    "rodar os testes",
};
#define N_OPCOES (int)(sizeof(OPCOES) / sizeof(OPCOES[0]))

void menu(void) {
  printf("\n");
  for (int i = 1; i < N_OPCOES; i++) printf("%d - %s\n", i, OPCOES[i]);
  printf("0 - %s\n", OPCOES[0]);
}

int ler_opcao(void) {
  char linha[32];
  char *fim;
  long opcao;

  if (!ler_texto("opcao: ", linha, sizeof(linha))) return 0;
  opcao = strtol(linha, &fim, 10);
  if (fim == linha || *fim != '\0' || opcao < 0 || opcao >= N_OPCOES) return -1;
  return (int)opcao;
}

int main(void) {
  int opcao;

  printf("cifra de Vigenere: letras A-Z/a-z, o resto passa sem mudar\n");

  while (menu(), (opcao = ler_opcao()) != 0) {
    switch (opcao) {
      case 1:
        processar_digitado(1);
        break;
      case 2:
        processar_digitado(-1);
        break;
      case 3:
        rodar_testes();
        break;
      default:
        printf("  opcao invalida\n");
    }
  }

  return 0;
}
