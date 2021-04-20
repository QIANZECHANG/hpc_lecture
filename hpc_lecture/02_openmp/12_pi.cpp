#include <cstdio>

int main() {
  int n = 10;
  double dx = 1. / n;
  double pi = 0;
double a[n];
#pragma omp parallel for
  for (int i=0; i<n; i++) {
    a[i] = (i + 0.5) * dx;
  }
#pragma omp parallel for shared(a)
  for (int i=0; i<n; i++) {
#pragma omp atomic update
    pi += 4.0 / (1.0 + a[i] * a[i]) * dx;
  }
  printf("%17.15f\n",pi);
}
