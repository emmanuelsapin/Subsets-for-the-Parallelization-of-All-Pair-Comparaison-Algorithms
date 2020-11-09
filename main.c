/***************************************************************************************************************************************************
*
*                                 This program outputs the composing of the subsets for a number of individuals entered as parameter
*                                 
****************************************************************************************************************************************************/
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>



#define NMAX 20000 
#define MAXPOP NMAX*NMAX
#define MAXGROUP NMAX*NMAX+NMAX



int fillgroups(char pathtresult[],int n, int ntop, int sqrtntop)
{	FILE * fileresult;
	if ((fileresult = fopen(pathtresult, "w")) == NULL) 
	{	printf("file %s not found\n",pathtresult);		
		return (1);
	}
	printf("File %s opened.\nThe composition of the chunks are in the file in argument with one line per chunk and the element IDs separated by a space",pathtresult);
	int groupnumber=0;
	int n1;
	int group;
	for(n1=0;n1<ntop;n1=n1+sqrtntop)
	{	int n2;
		for(n2=n1;n2<n1+sqrtntop;n2++)
		{	if (n2<=n) fprintf(fileresult,"%d ",n2);
		};
		fprintf(fileresult,"\n");
		groupnumber++;
	};
	
	for(n1=0;n1<sqrtntop;n1++)
	{	int n2;
		for(n2=0;n2<sqrtntop;n2++)
		{	if (n1+n2*sqrtntop<n) fprintf(fileresult,"%d ",n1+n2*sqrtntop);
		};
		groupnumber++;
		fprintf(fileresult,"\n");
	};
	int moveup[sqrtntop];
	for(n1=0;n1<sqrtntop;n1++)
	{	moveup[n1]=0;
	};
	int increment=1;
	do 
	{	for(n1=1;n1<sqrtntop;n1++)
		{	moveup[n1]=(n1*increment )%(sqrtntop);
		};
		for(n1=0;n1<sqrtntop;n1++)
		{	int n2;
			for(n2=0;n2<sqrtntop;n2++)
			{	if ((n1+moveup[n2])%sqrtntop+n2*sqrtntop<=n) fprintf(fileresult,"%d ",(n1+moveup[n2])%sqrtntop+n2*sqrtntop);
			};
			groupnumber++;
			fprintf(fileresult,"\n");
		};
		increment++;
	} while (increment<sqrtntop);
	fclose(fileresult);
};
 

//
//  main program
//	
int main(int argc, char *argv[])
{	clock_t begin = clock();
	printf("start....\n");
	//
	printf("Reading arguments...\n");
	//
	int n;
	if (argc<2)
    {   printf("Argument 1 is number of observations and is missing. Default is 25\n");
		n=25;
	} else 
	{	n = atoi (argv[1]);
	};
	printf("Number of observations is %d.\n",n);
	char pathtresult[200]; 
	if (argc<3)
    {   printf("Argument 2 is file to store the result and is missing. Default is \"chunks.txt\"\n");
		strcpy(pathtresult,"chunks.txt");
	} else 
	{	strcpy(pathtresult,argv[2]);
	};
	printf("The path of the file to store the result is %s.\n",pathtresult);
	int person;
	int group;
	int i=ceil(sqrt(n));
	int flag=0;
	do
	{	flag=0;
		int j;
		for(j=2;j<ceil(i/2)+1;j++)
		{	if(i%j==0)
			{	flag=1;
				j=i-1;
			};
		}; 
		if (flag==1) i++;
	} while (flag==1 && i<10000); 
	printf("The lowest square of a prime number higher than %d is %d.\n",n,i*i);
	int ntop=i*i;
	if (ntop>MAXPOP)
	{	printf("This number of individuals is too high and can not be handle at the moment.\nPlease contact me at emmanuelsapin@hotmail.com");
		exit(1); 
	};
	int sqrtntop=i;
	int nbgroupperperson=sqrtntop+1;
	int nbgroup=ntop+sqrtntop;
	printf("Number of elements in the matrix = %d\nNumber of person per group = %d\nNumber of group per person = %d\nNumber of groups = %d\n", ntop, sqrtntop, nbgroupperperson,nbgroup);
	printf("Creation of the chunks:\n");
	fillgroups(pathtresult,n,ntop,sqrtntop);
	clock_t end = clock();
	float elapsed_secs = (float)(end - begin);
    printf("\nTotal time:%f cpu click so %f seconds",elapsed_secs,elapsed_secs/CLOCKS_PER_SEC );
	return (0);
} 
