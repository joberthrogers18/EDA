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

}

int main(int argc, char * argv[])
{

  return 0;
}
