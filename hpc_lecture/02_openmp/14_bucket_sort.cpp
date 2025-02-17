#include <cstdio>
#include <cstdlib>
#include <vector>

int main() {
  int n = 50;
  int range = 5;
  std::vector<int> key(n);
#pragma omp parallel for
  for (int i=0; i<n; i++) {
    key[i] = rand() % range;
    printf("%d ",key[i]);
  }
  printf("\n");

  std::vector<int> bucket(range,0);
#pragma omp parallel for shared(bucket)
  for (int i=0; i<n; i++)
#pragma omp atomic update
    bucket[key[i]]++;
  std::vector<int> offset(range,0);
  std::vector<int> a(range,0);  
#pragma omp parallel for
  for (int i=1; i<range; i++){ 
#pragma omp parallel for shared(a)
    for (int j=0; j<i; j++){
#pragma omp atomic update
       a[i] += bucket[j];
    }
    offset[i] = a[i];
  }
#pragma omp parallel for
  for (int i=0; i<range; i++) {
    int j = offset[i];
    for (; bucket[i]>0; bucket[i]--) {
       key[j++] = i;
    }
  }

  for (int i=0; i<n; i++) {
    printf("%d ",key[i]);
  }
  printf("\n");
}
