#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

size_t count = 0;
long long pSum = 0;

typedef struct {
  long long w;
  long long p;
} Item;

void printItems(const bool *mask, size_t N, FILE *out) {
  for (size_t i = 1; i < N + 1; ++i) {
    if (mask[i] == true) {
      fprintf(out, "%lu ", i);
    }
  }
}

void countPrice(const long long **A, const Item *items, bool *inBag, const size_t N, const long long W) {
  if (A[N][W] == 0) {
    return;
  }

  if (A[N - 1][W] == A[N][W]) {
    countPrice(A, items, inBag, N - 1, W);
  } else {
    countPrice(A, items, inBag, N - 1, W - items[N].w);
    inBag[N] = true;
    count++;
    pSum += items[N].p;
  }
}

int main() {
  size_t N = 0;
  long long W = 0;

  FILE *in = fopen("input.txt", "r");

  fscanf(in, "%lu  %lld ", &N, &W);

  Item *items = calloc(N + 1, sizeof(Item));

  for (size_t i = 1; i < N + 1; ++i) {
    fscanf(in, "%lld %lld", &items[i].w, &items[i].p);
  }

  fclose(in);

  long long **A = calloc(N + 1, sizeof(long long *));

  for (int i = 0; i < N + 1; ++i) {
    A[i] = calloc(W + 1, sizeof(long long));
  }

  for (size_t k = 1; k < N + 1; ++k) {
    for (long long s = 1; s < W + 1; ++s) {///Перебираем для каждого k все вместимости
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

  fprintf(out, "%lld %lu\n", pSum, count);

  printItems(inBag, N, out);

  fclose(out);

  for (int i = 0; i < N + 1; ++i) {
    free(A[i]);
  }

  free(A);
  free(items);
  free(inBag);

  return 0;
}
