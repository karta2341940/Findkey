#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct Record
{
    char front[512];
    char back[512];
}Record;


int TotalR(int t);
int s(int n);
int c(int n,int r);
void *brackets (char *relation);
void *optimized(char ** strfd,int num);

int main()
{
    char relation[1024];
    int num_input=0;
    FuncD *fd;
    Record *record = calloc(TotalR(r_total),sizeof(Record*));
    scanf("%s",relation);
    strcpy(relation , (char*)brackets(relation));
    scanf("%d",&num_input);


    return 0;
}


/**
 * This function is in order to find the key of input relation
 */
void *generate(int words,int Layer)
{

    for ( int i = 0 ; i < words ; i++ )
    {

    }
}

/**
 * Make the input relation into pure word array
 * @param relation The array that the first line that you input
 */
void *brackets(char*relation)
{
    char *temp,*temp2;
    int not_name=0,indexN=0;
    int len = strlen(relation),len2=0;
    temp = malloc(len*sizeof(char));
    strcpy(temp,relation);
    for(int i = 0 ; i < len-1; i++)
    {
        if(relation[i] == '(')
        {
            not_name++;
        }
        else if(relation[i] == ')')
        {
            not_name=0;
        }
        if(not_name)
        {
            //temp[indexN] = relation[i];
            strcpy(&temp[indexN],&relation[i]);
            indexN++;
        }
    }
    len2=strlen(temp);
    temp2 = malloc((len2-2)*sizeof(char));
    
    {
        int j=0;
        for(int i = 0 ; i < len2 ; i++)
        {
            if( i != 0 && i != len2-1 )
            {
                temp2[j]= temp[i];
                j++;
            }
        }
    }

    return temp2;
}
/**
 * Made the formation AB->C into ab and c
 * @param strfd The array of fd as string array
 * @param fdnum The total number of fd
 */
void *optimized(char ** strfd,int fdnum)
{
    FuncD *fd = malloc( fdnum * sizeof(FuncD));
    
    for(int i =  0 ; i < fdnum ;i++)
    {
        fd[i].back = strfd[i][strlen(strfd[i])-1];
        for(int j = 0 ; j < strlen(strfd[i]); j++ )
        {
            if( strfd[i][j] == '-')
            {
                break;
            }
            else if(strfd[i][j] != '-')
            {
                fd[i].front[j] = strfd[i][j];
            }
        }
        //printf("%s,%c\n",fd[i].front,fd[i].back);
    }
    return fd;
}
int s(int n)
{
    int result=1;
    for(int i = 1 ; i <= n ; i++) result = i*result;
    return result;
}
/**
 * Combination
 * Get r in n;
 */
int c(int n,int r)
{
    return s(n) / ( s(r)*s(n-r));  
}
int TotalR(int t)
{
    int a=0;
    for(int i = 1 ; i <= t ; i ++) a = a + c(t,i);
    return a; 
}