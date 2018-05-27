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

int peekA()
{
   return A[posA-1];
}

int peekB()
{
   return B[posB-1];
}

int peekC()
{
   return C[posC-1];
}

void moveAB ()
{
  if(posA == 0)
  {
    pushA(popB());
  }
  else if(posB == 0)
  {
    pushB(popA());
  }
  else if (peekB() < peekA())
  {
    pushA(popB());
  }
  else if (peekA() < peekB())
  {
    pushB(popA());
  }

}

void moveAC ()
{
  if(posA == 0)
  {
    pushA(popC());
  }
  else if(posC == 0)
  {
    pushC(popA());
  }
  else if (peekC() < peekA())
  {
    pushA(popC());
  }
  else if (peekA() < peekC())
  {
    pushC(popA());
  }
}

void moveBC ()
{
  if(posB == 0)
  {
    pushB(popC());
  }
  else if(posC == 0)
  {
    pushC(popB());
  }
  else if (peekC() < peekB())
  {
    pushB(popC());
  }
  else if (peekB() < peekC())
  {
    pushC(popB());
  }
}

int main(int argc, char * argv[])
{
  initialize();
  show();
  while(posB < 8)
  {
    moveAC();
    show();
    if(posB == 8)break;
    moveAB();
    show();
    if(posB == 8)break;
    moveBC();
    show();
  }
  show();

  return 0;
}
