#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

size_t count = 0;
long long pSum = 0;

void printItems(long long **A, long long *w, size_t k, long long s, FILE *out) {
  if (A[k][s] == 0) {
    return;
  }

  if (A[k - 1][s] == A[k][s]) {
    printItems(A, w, k - 1, s, out);
  } else {
    printItems(A, w, k - 1, s - w[k], out);
    fprintf(out, "%lu ", k);
  }
}

void countPrice(long long **A, long long *w, long long *p, size_t k, long long s) {
  if (A[k][s] == 0) {
    return;
  }

  if (A[k - 1][s] == A[k][s]) {
    countPrice(A, w, p, k - 1, s);
  } else {
    countPrice(A, w, p, k - 1, s - w[k]);
    count++;
    pSum += p[k];
  }
}

int main() {
  size_t N = 0;
  long long W = 0;

  FILE *in = fopen("input.txt", "r");

  fscanf(in, "%lu  %lld ", &N, &W);

  long long *w = calloc(N + 1, sizeof(long long));
  long long *p = calloc(N + 1, sizeof(long long));

  for (size_t i = 1; i < N + 1; ++i) {
    fscanf(in, "%lld %lld", &w[i], &p[i]);
  }

  fclose(in);

  long long **A = calloc(N + 1, sizeof(long long *));

  for (int i = 0; i < N + 1; ++i) {
    A[i] = calloc(W + 1, sizeof(long long));
  }

  for (size_t k = 1; k < N + 1; ++k) {
    for (long long s = 1; s < W + 1; ++s) {///Перебираем для каждого k все вместимости
      if (s >= w[k]) {///Если текущий предмет вмещается в рюкзак
        A[k][s] = max(A[k - 1][s], A[k - 1][s - w[k]] + p[k]);////Выбираем класть его или нет
      } else {
        A[k][s] = A[k - 1][s];///Иначе, не кладем
      }
    }
  }

  FILE *out = fopen("output.txt", "w");

  countPrice(A, w, p, N, W);

  fprintf(out, "%lld %lu\n", pSum, count);

  printItems(A, w, N, W, out);

  fclose(out);

  for (int i = 0; i < N + 1; ++i) {
    free(A[i]);
  }

  free(A);
  free(w);
  free(p);

  return 0;
}
