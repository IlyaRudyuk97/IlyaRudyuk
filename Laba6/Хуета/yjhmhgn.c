#include <stdio.h>

int main ()
{
   FILE * pFile;
   int n=3;
   int n1[n];
   //char name [100];
    for (int i=0 ; i<n ; i++)
   {
     read("%d",&n1[i]);
   }
   pFile = fopen ("myfile.txt","w");
    for (int i=0 ; i<n ; i++)
   {
     fprintf (pFile, "%d\n",n1[i]);
   }
   fclose (pFile);
 
   return 0;
}
