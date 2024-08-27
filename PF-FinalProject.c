#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main ()
{
	int i , c , x , j ; 														//used as counters in loops
	int rec = 0 , space = 0 , hspace = 0 , count=0 ; 							//used as counters to keep track
	int searchlen , headlen , mtcount , tempcount , finlen, count2, terminate;						//used to track counts and lengths
	int  mcount [40];															//used to keep track of matched articles
	char hold, num ;															//used as temp holders 
	char multsear[100], finsearch[100] = (""), multi[5][100] ;					//used in sentence searches
	char temphead [100] , search [50] , var [50] ;								//used to match and keep record of articles
	char mhead[40][100], mthead [100];    										//used to record matched article titles
	
	FILE *file;
	file = fopen ("articles.txt" , "r");
	
	printf ("Search : ");
	fflush(stdin);																
	gets (search);
	searchlen = strlen (search);
	
	for (c=0;c<searchlen;c++)	//loop to check how many words the entered string has
	{
		hold = search [c];
		if (hold==' ')
		space++;
	}	
//	printf ("%d", space);

	if (space==0)				//SEARCH FOR SINGLE WORDS
	{
	fgets (temphead,10000,file);
	
	headlen = strlen (temphead);
	for (x=0;x<headlen;x++)
	{
		num = search [x];
		if (num==' ')
		hspace++;
	}
	while(!feof(file))
	{
	
	do{	
	fscanf(file,"%s", var);			//scanning each word to check if it matches the search
	strlwr (var);
	strlwr (search);
	
//	printf ("%s\n", var);
//	printf ("%s\n", search);

    count2=0;
    terminate=0;
    for(i=0;i<strlen(search)&&!terminate;++i)
    {
    	if(search[i]==var[i])
    	++count2;
    	else
    	terminate=1;
	}
	
	if (count2==strlen(search) && strlen(search)>6)
	{
		count++;
		count++;
	}
	
	else if (count2>strlen(search)/2 && strlen(search)>6)
	{
		count++;
	}
	
	else if(count2==strlen(search))
	count++;
	
	}while(var[0]!='@');			//breaking loop when a new article starts
	
	if (count>=1)					//storing article if it matches
	{
//		printf ("%s\t", temphead);
		mcount[rec] = count;
		strcpy (mhead[rec],temphead);
//		printf ("%s\n", mhead[rec]);
		rec++;
	}
//	printf ("matches in file = %d\n", count);

	count=0;						//resetting count for new article
	
	fflush(stdin);
	fgets (temphead,10000,file);
	fgets (temphead,10000,file);
	
	}
	mthead [0]='/0';				//temp variable introduced to sort articles
	
	for (j=0;j<rec;j++)				//sorting articles by relevance (number of matches)
	{
		for (i=j+1;i<rec;i++)
		{
			if (mcount[j] < mcount[i])
			{
		//		printf ("Yes");
				mtcount = mcount [i];
				mcount[i] = mcount [j];
				mcount[j] = mtcount;
				strcpy (mthead,mhead[i]);
				strcpy (mhead[i],mhead[j]);
				strcpy (mhead[j],mthead);				
			}
		}
	}
	
	//printing the final results of the search.
	
	printf ("Following are the matches to your search by relevance \n\n");
	
	if (rec == 0)
	printf ("No matched searches found, please try a different keyword!\n");
	
	else
	{
	
	for (i=0;i<rec;i++)
	{
		printf ("Title %d : %s\n",i+1,mhead[i]);
	}
	
	rewind(file);
	int n, tru=0;
	printf("Enter title no. of which you want to print article of: ");
	scanf("%d",&n);
	n-=1;
	fgets (temphead,10000,file);

	while(!feof(file))
	{
		tru=0;
		if(strcmp(temphead,mhead[n])==0)
	    tru=1;
	fscanf(file,"%s", var);
	while(var[0]!='@')
	
	{
	if(tru)
	printf("%s ",var);
	var[0]='\0';
	fscanf(file,"%s", var);
	}		
	
	fflush(stdin);
	fgets (temphead,10000,file);
	fgets (temphead,10000,file);
		}
	}
	
	}

	else if (space >= 1)			//search for multiple words
	{
		
		fgets (temphead,10000,file);
		
		if (strcmp(temphead,search)==0)			//checking if heading matches search
		count++;
		
		while (!feof(file))					
		{
			
		for (j=0;j<=space;j++)		//scanning as many words as entered and storing in a 2d string array
		{	
			fscanf (file,"%s", multi[j] ); 
		//	printf ("%s", multi[j]);
		}
		
		for (j=0;j<=space;j++)		//converting array to a string so that it can be matched
		{
		strcat (finsearch,multi[j]);
		if (j!=space)
		strcat (finsearch," ");
		}
		
		do{
			strlwr(finsearch);
//			printf ("%s %s\n",finsearch,search);

			if (strcmp(finsearch,search)==0)		//checking match
			{
				count++;
//				printf ("count = %d", count);
			}
			
			fscanf(file, "%s", var);				//scanning the next word	
//			printf ("%s ", var);

			for (j=0;j<space;j++)					//taking each word one index up to remove the first word and make space for the newly scanned word
			{
			strcpy (multi[j],multi[j+1]);	
			}
			
			strcpy (multi[j],var);					//storing the last scanned word into the array
			
			finlen = strlen (finsearch);			//clearing the string to store the new array in it
			for (j=0;j<finlen;j++)
			{
				finsearch[j] = '\0';
			}
			
			for (j=0;j<=space;j++)					//storing new array as a sentence
			{
			strcat (finsearch,multi[j]);
			if (j!=space)
			strcat (finsearch," ");
			}
			
			}while(var[0]!='@');					//breaking loop if article ends else it continues to find matches
			
//			printf ("%d", count);
			if (count>=1)							//if matched storing data
			{
			mcount[rec] = count;
			strcpy (mhead[rec],temphead);
//			printf ("%s\n", mhead[rec]);
			rec++;
			}
			
			count = 0;								//resetting count
			
			fflush(stdin);
			fgets (temphead,10000,file);			//scanning title of next article
			fgets (temphead,10000,file);
		}
		
		mthead [0]='/0';			//introducing temp var to sort articles
		
	for (j=0;j<rec;j++)				//sorting articles according to relevance
	{
		for (i=j+1;i<rec;i++)
		{
			if (mcount[j] < mcount[i])
			{
		//		printf ("Yes");
				mtcount = mcount [i];
				mcount[i] = mcount [j];
				mcount[j] = mtcount;
				strcpy (mthead,mhead[i]);
				strcpy (mhead[i],mhead[j]);
				strcpy (mhead[j],mthead);				
			}
		}
	}
	
	//printing the final resuls after the scan
	
	printf ("Following are the matches to your search by relevance \n\n");
	
	if (rec == 0)
	printf ("No matched searches found, please try a different keyword!\n");
	else
	
	{

	for (i=0;i<rec;i++)
	{
		printf ("Title %d : %s\n",i+1,mhead[i]);
	}	
	
		rewind(file);
	int n, tru=0;
	printf("Enter title no. of which you want to print article of: ");
	scanf("%d",&n);
	n-=1;
	fgets (temphead,10000,file);

	while(!feof(file))
	{
		tru=0;
		if(strcmp(temphead,mhead[n])==0)
	    tru=1;
	fscanf(file,"%s", var);
	while(var[0]!='@')
	
	{
	if(tru)
	printf("%s ",var);
	var[0]='\0';
	fscanf(file,"%s", var);
	}		
	
	fflush(stdin);
	fgets (temphead,10000,file);
	fgets (temphead,10000,file);
		}
	}
	}	

		
	fclose(file);
}