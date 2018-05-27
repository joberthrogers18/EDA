#include <stdio.h>

int A[8];
int B[8];
int C[8];

int posA = 0;
int posB = 0;
int posC = 0;

void pushA (int n)
{
  A[posA] = n;
  posA++;

}

int popA ()
{
  posA--;
  return A[posA];
}

void pushB (int n)
{
  B[posB] = n;
  posB++;

}

int popB ()
{
  posB--;
  return B[posB];
}

void pushC (int n)
{
  C[posC] = n;
  posC++;

}

int popC ()
{
  posC--;
  return C[posC];
}

void show ()
{
  int i;
  printf("A: ");
  for(i = 0; i < posA; i++)
  {
    printf("%d ", A[i]);
  }
  printf("\n");

  printf("B: ");
  for(i = 0; i < posB ; i++)
  {
    printf("%d ", B[i]);
  }
  printf("\n");

  printf("C: ");
  for(i = 0; i < posC; i++)
  {
    printf("%d ", C[i]);
  }
  printf("\n");

}

void initialize ()
{
  int i;

  for(i = 8; i >= 1; i--){
    pushA(i);
  }

}

int peekA(){
  
}

void moveAB ()
{

}

void moveAC ()
{

}

void moveBC ()
{

}
int main(int argc, char * argv[])
{
  initialize();
  show();

  return 0;
}
