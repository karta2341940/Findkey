#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define boolean char
boolean debug = 1;

void * getword(char* relation);
void fd_deal(char** fds,int number_of_fds);
char* strreplace(char * ,const char*);
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

}

void * getword(char* relation)
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

void fd_deal(char** fds,int number_of_fds)
{
    for(int i = 0 ; i <strlen(fds) ; i++ )
    {
        //strreplace();
        //fds[i] 
    }
}

char* strreplace(char * src,const char* replace)
{
    strstr(src,replace);

}