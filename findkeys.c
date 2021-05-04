#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define boolean char
boolean debug = 1;
#define nullptr NULL


void * getword(char* relation);
void fd_deal(char** fds,int number_of_fds);
char* strreplace(char *,const char*,const char*);
int s(int n);
int c(int n,int r);
int TotalR(int t);
char** general_closure(int relation_words);
void general_binary_code(int input,int relation_words);


int main()
{
    char relation[1024];
    scanf("%s",relation);

    getword(relation);
    if(debug)printf("%s\n",relation); //debug
    int number_of_fd = 0;
    scanf("%d",&number_of_fd);
    if(debug)printf("%d\n",number_of_fd); //debug
    char** fds =calloc(number_of_fd,sizeof(char*));
    for( int i = 0 ; i < number_of_fd ; i ++ )
    {
        fds[i] = calloc(512,1);//initial the string into a 512 bytes dual array
        scanf("%s",fds[i]);
        if(debug)printf("%s\n",fds[i]); // debug
    }
    fd_deal(fds,number_of_fd);

    general_closure(strlen(relation));
}

/**
 * To remove schema's name and parentheses and return the string
 * @param relation The input schema
 */
void* getword(char* relation)
{
    char* temp = calloc(strlen(relation),sizeof(char));
    for( int i = 0 ; i < strlen(relation) ; i ++ )
    {
        if(relation[i] == '(')
        {
            for( int j = i+1 ; j < strlen(relation)-1 ; j++ )
            {
                temp[j-(i+1)]=relation[j];
            }
            break;
        }
    }
    return strcpy(relation,temp);
}
/**
 * Turn the formate abc->c into abc,c
 * @param fds The fd that you input
 * @param number_of_fds The total number of fds
 */
void fd_deal(char** fds,int number_of_fds)
{
    for(int i = 0 ; i <number_of_fds ; i++ )
    {
        strreplace(fds[i],"->",",");
        if(0)printf("\t%s\t\n",fds[i]);
    }
}
/**
 * To replace the SRC into TARGET in DEST
 */
char* strreplace(char * dest,const char* src,const char* target)
{
    char *x =strstr(dest,src);
    int y = x - dest ;
    if(0)//debug
    {
        printf("%p,%p\n",dest,strstr(dest,src));
        printf("%s is at the position %d\n",src,y);
    }
    if(!x)
    {
        printf("%s not found\n",src);
        return nullptr;
    }
    else if(x)
    {
        char * temp = calloc( strlen(dest) - strlen(src) + strlen(target) , sizeof(char) );
        char * temp2 = calloc( strlen(dest) - strlen(src) + strlen(target) , sizeof(char) );
        strncpy(temp,dest,y);//fd的前面
        strncpy(temp2,x+strlen(src),strlen(dest)-y-strlen(src));//儲存fd的後面
        strncat(temp,target, strlen(target));//加逗號
        strncat(temp,temp2,strlen(temp2));
        return strcpy(dest,temp);//return to dest
    }
}
/**
 * To general closure
 */
char** general_closure(int relation_words)
{
    char **closure = calloc( TotalR(relation_words) , sizeof(char*) );
    for( int i = 1 ; i < TotalR(relation_words)+1 ; i++ )
    {
         printf("%d\t",i);
        general_binary_code(i,relation_words);
    }
}
void general_binary_code(int input,int relation_words)
{
    
    int i =relation_words;
    char* temp = calloc(relation_words,sizeof(char));
    while ( i != 0 )
    {
        temp[i] = 30+(input%2);
        input = input/2;
        i--;
    }
    printf("%ld",sizeof(temp));
    printf("\n");
}























//------------------------Math----------------
int s(int n)
{
    int result=1;
    for(int i = 1 ; i <= n ; i++) result = i*result;
    return result;
}
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