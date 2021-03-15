#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

size_t count = 0;
unsigned long long pSum = 0;

typedef struct {
  unsigned long long w;
  unsigned long long p;
} Item;

void printItems(const bool *mask, size_t N, FILE *out) {
  for (size_t i = 1; i < N + 1; ++i) {
    if (mask[i] == true) {
      fprintf(out, "%lu ", i);
    }
  }
}

void countPrice(const unsigned long long **A, const Item *items, bool *inBag, const size_t N, unsigned long long W) {
  for (size_t i = N; i > 0; --i) {
    if (A[i][W] == 0) {
      break;
    }

    if (A[i - 1][W] != A[i][W]) {
      inBag[i] = true;
      count++;
      pSum += items[i].p;
      W -= items[i].w;
    }
  }
}

int main() {
  size_t N = 0;
  unsigned long long W = 0;

  FILE *in = fopen("input.txt", "r");

  fscanf(in, "%lu  %llu ", &N, &W);

  Item *items = calloc(N + 1, sizeof(Item));

  for (size_t i = 1; i < N + 1; ++i) {
    fscanf(in, "%llu %llu", &items[i].w, &items[i].p);
  }

  fclose(in);

  unsigned long long **A = calloc(N + 1, sizeof(unsigned long long *));

  for (size_t i = 0; i < N + 1; ++i) {
    A[i] = calloc(W + 1, sizeof(unsigned long long));
  }

  for (size_t k = 1; k < N + 1; ++k) {
    for (unsigned long long s = 1; s < W + 1; ++s) {///Перебираем для каждого k все вместимости
      if (s >= items[k].w) {///Если текущий предмет вмещается в рюкзак
        A[k][s] = max(A[k - 1][s], A[k - 1][s - items[k].w] + items[k].p);////Выбираем класть его или нет
      } else {
        A[k][s] = A[k - 1][s];///Иначе, не кладем
      }
    }
  }

  FILE *out = fopen("output.txt", "w");

  bool *inBag = calloc(N + 1, sizeof(bool));

  countPrice(A, items, inBag, N, W);

  fprintf(out, "%llu %lu\n", pSum, count);

  printItems(inBag, N, out);

  fclose(out);

  for (size_t i = 0; i < N + 1; ++i) {
    free(A[i]);
  }

  free(A);
  free(items);
  free(inBag);

  return 0;
}
