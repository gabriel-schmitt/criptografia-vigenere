# Cifra de Vigenère

TDE de Estrutura de Dados II (UCS): implementação e teste da cifra de Vigenère em C.

```sh
make
./vigenere
```

## Método

Cada letra do texto é deslocada no alfabeto, como na cifra de César, mas o deslocamento vem de uma palavra-chave repetida ao longo do texto (A = 0, B = 1, …, Z = 25):

```text
texto:  A T T A C K A T D A W N
chave:  L E M O N L E M O N L E
cifra:  L X F O P V E F R N H R
```

Cifrar é `(T + K) mod 26` e decifrar é `(C - K) mod 26`. Como a mesma letra vira letras diferentes conforme a posição, a contagem de frequência que quebra a César não funciona direto. A cifra foi descrita por Giovan Battista Bellaso em 1553 e atribuída depois a Blaise de Vigenère. Friedrich Kasiski publicou em 1863 um método para quebrá-la, que procura repetições no texto cifrado para descobrir o tamanho da chave.

A implementação foi escrita a partir da descrição do método. Espaços, pontuação e letras acentuadas passam sem alteração e não consomem chave. Maiúsculas e minúsculas são preservadas.

## Testes

```text
  teste 1, chave "LEMON"
    original:  ATTACKATDAWN
    cifrado:   LXFOPVEFRNHR
    decifrado: ATTACKATDAWN
    volta ao original: sim
    confere com a fonte (LXFOPVEFRNHR): sim

  teste 2, chave "UCS"
    original:  Estrutura de Dados II: criptografia e legal!
    cifrado:   Yullwlots xg Vufgm KA: wtajvgatszks y nwacd!
    decifrado: Estrutura de Dados II: criptografia e legal!
    volta ao original: sim

  teste 3, chave "ABCD"
    original:  AAAAAAAAAAAAAAAA
    cifrado:   ABCDABCDABCDABCD
    decifrado: AAAAAAAAAAAAAAAA
    volta ao original: sim

  teste 4, chave "D"
    original:  ATACAR AO AMANHECER
    cifrado:   DWDFDU DR DPDQKHFHU
    decifrado: ATACAR AO AMANHECER
    volta ao original: sim
```

1. Bate com o exemplo da Wikipédia.
2. Texto comum: os dois `i` de "criptografia" viram `a` e `k`.
3. Texto repetitivo expõe a chave no cifrado, que é a fraqueza explorada por Kasiski.
4. Com chave de uma letra, a Vigenère vira a cifra de César.

O código está em `vigenere.c`.

## Fontes

- <https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher>

## Uso de IA

Feito com apoio do Claude Opus 5.5 (Anthropic) na escolha do algoritmo, na escrita e revisão do código, nos testes e no rascunho deste relatório. As decisões foram minhas, com a IA como par de programação.
