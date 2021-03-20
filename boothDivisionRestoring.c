#include <stdio.h>

void binout_helper(int in, int left) {
  if (left == 0) return;
  binout_helper(in >> 1, left - 1);
  printf("%d",in & 1);
}

void binout(int in) {
  binout_helper(in,8);
}

void print_status(int Q,int A, int M) {
  printf("Q: %3d, A: %3d, M: %3d [",Q,A,M);
  binout(A); printf(" ");
  binout(Q); printf("]\n");
}

int main() {
  unsigned char dividend = 17;
  unsigned char divisor = 5;

  // NOTE: In a real binary division circuit, A would have one more bit than Q
  unsigned char A = 0;
  unsigned char Q = dividend;
  unsigned char M = divisor;
  printf("\nBooth Restoring Division\n");
  print_status(Q,A,M);

  for (int i = 0; i < 8; i++) {

    // Step 1: Shift A and Q left
    int AQ = (A << 8) + Q;
    AQ <<= 1;
    A = (AQ >> 8) & 0xFF;
    Q = AQ & 0xFF;

    // Step 2: Subtract M from A, place answer in A
    A -= M;

    if (A & (1 << 7)) {
      // If the sign bit of A is 1, set q_0 to 0 
      Q &= ~1;
      // and add M back to A (restore A)
      A += M;
    } else {
      // otherwise, set q_0 to 1
      Q |= 1;
    }

    print_status(Q,A,M);
  }

  unsigned char quotient = Q;
  unsigned char remainder = A;
  printf("\nBooth Restoring Division\n");
  printf("%d / %d = %d\n" ,dividend,divisor,quotient);
  printf("%d %% %d = %d\n",dividend,divisor,remainder);
  return 0;
}