#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define boolean char
boolean debug = 0;
#define nullptr NULL

typedef struct findkeys
{
    char*** isolationfd;// Isolating fd's right and left
    char** right;
    char** left;
    char** fds;
    int total_word;
    int number_of_fds;
}findkeys;

void * getword(char* relation);
void fd_deal(char** fds,int number_of_fds);
char* strreplace(char *,const char*,const char*);
int s(int n);
int c(int n,int r);
int TotalR(int t);
char** general_closure(int relation_words,char* relation);
void* general_binary_code(int input,int relation_words,char* closure);
char * upper (char * fds);
findkeys find_key(findkeys* findkeys);
void ***isolation(findkeys* findkey);



int main( int arg , char**args )
{
    system("clear");//clear screen
    int i ;
    char relation[1024];
    scanf("%s",relation);//scan schema
    getword(upper(relation));
    if(debug)printf("%s\n",relation); //debug
    int number_of_fd = 0;
    scanf("%d",&number_of_fd);//scan the number of fd
    if(debug)printf("%d\n",number_of_fd); //debug
    char** fds =calloc(number_of_fd,sizeof(char*));
    for(  i = 0 ; i < number_of_fd ; i ++ )
    {
        fds[i] = calloc(512,1);//initial the string into a 512 bytes dual array
        scanf("%s",fds[i]);
        upper(fds[i]);
        if(debug)printf("%s\n",fds[i]); // debug
    }

    fd_deal(fds,number_of_fd);

    

    findkeys findkeys;
    findkeys.right = general_closure(strlen(relation),relation);;
    findkeys.left = calloc(TotalR(strlen(relation)),sizeof(char*));
    findkeys.number_of_fds=number_of_fd;
    findkeys.total_word=strlen(relation);
    findkeys.fds=fds;

    
    for( i = 0; i < 15 ;i ++)
    {
        findkeys.left[i] = calloc(strlen(relation)+1,sizeof(char));
        //printf("{%s}",findkeys.left[i]);
        //printf("\n");
    }
    
    find_key(&findkeys);
    

}

/**
 * Turn the formate abc->c into abc,c
 * @param fds The fd that you input
 * @param number_of_fds The total number of fds
 */
void fd_deal(char** fds,int number_of_fds)
{
    int i;
    for( i = 0 ; i <number_of_fds ; i++ )
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
char** general_closure(int relation_words,char* relation)
{
    char **closure = calloc( TotalR(relation_words) , sizeof(char*) );
    char **closure2 = calloc( TotalR(relation_words) , sizeof(char*) );
    int input;
    for(  input = 0 ; input < TotalR(relation_words) ; input++ )
    {
        closure[input] = calloc(relation_words,sizeof(char));
        closure2[input] = calloc(relation_words+1,sizeof(char));
        //closure[input] = general_binary_code(input,relation_words,closure[input]);
        general_binary_code(input,relation_words,closure[input]);
        
        int j = 0,i;
        for( i = 0 ; i < relation_words ; i++)
        {
            if(closure[input][i])
            {
                closure2[input][j]=relation[i];
                j++;
            }
        }
    }
    int i;
    for( i = 0 ; i < 15; i ++ )
    {
        closure[i] = closure2[i];
        if(0)
        {
            printf("{%s}",closure[i]);
            printf("\n");
        }
    }
    return closure;
}
void* general_binary_code(int input,int relation_words,char* closure)
{
    input = input+1;
    int in =0;
    while ( in != relation_words )
    {
        int x = (input % 2);
        closure[in] = x;
        //printf("%d",closure[in]);
        input = input/2;
        in++;
    }

    //if(debug)for(int i = 0 ; i < relation_words ; i++)
    //printf("%d",closure[i]);
    //printf("\n");
    
    return closure;
}
/**
 *Turn every lower word into upper
 */
char * upper (char * input)
{
    int i;
    for( i = 0 ; i < strlen( input ) ; i ++ )
    {
        if( input[i] > 90 )
        {
            input[i] = input[i]-32;
        }
    }
    return input;
}
/**
 * To find keys und superkeys
 * and also return struction findkey
 */
findkeys find_key(findkeys* findkeys)
{
    isolation(findkeys);
    int i,j,k,h;
    for(  i = 0 ; i < TotalR(findkeys -> total_word ) ; i++ )
    {
        int c = 0 ;
        //findkeys->isolationfd[number_of_fds][0_and_1][strlen(findkeys->isolationfd[number_of_fds][0_and_1])]
        //findkeys->right[TotalR(findkeys->total_word)][strlen(findkeys->right[TotalR(findkeys->total_word)])]
        for(  j = 0 ; j < strlen( findkeys->right[i] ) ; j++ )
        {
            for(  k = 0 ; k < findkeys->number_of_fds ; k++ )
            {
                for(  h = 0; h < strlen(findkeys->isolationfd[k][0]) ; h++ )
                {
                    if( findkeys->right[i][j] == findkeys->isolationfd[k][0][h] )
                    {
                        int fdl = strlen(findkeys->left[i]);
                        findkeys->left[i][c] = findkeys->isolationfd[k][1][0];
                        c++;
                    }
                }
            }
        }
        printf("{%s} = ",findkeys->right[i]);
        printf("{%s}\n",findkeys->left[i]);
    }
    /*
    for(int i = 0; i < 15 ;i ++)
    {
        printf("{%s}",findkeys->left[i]);
        printf("\n");
    }*/
    return *findkeys;
}

void ***isolation(findkeys* findkey)
{
    int i,j,k;
    void*** output = calloc( TotalR( findkey->total_word ) , sizeof(void**) ) ;
    for(  i = 0 ; i < TotalR( findkey->total_word ) ; i++ )
    {
        output[i] = calloc( 2 , sizeof(char*) );
        for(  j = 0 ; j < 2 ; j++ )
        {
            output[i][j] = calloc( findkey->total_word , sizeof(char) );
        }
    }
    findkey->isolationfd=(char***)output;
    for(  i = 0 ; i < findkey->number_of_fds ; i ++ )
    {
        int sw=0;
        int w = 0;
        for(  j = 0 ; j < strlen( findkey->fds[i] ) ; j++ )
        {   
            //printf("j:%d w:%d ",j,w); 
            if( findkey->fds[i][j] == ',' )
            {
                sw=1;
                w=0;
            }
            if( findkey->fds[i][j] != ',' )
            {
                findkey->isolationfd[i][sw][w] = findkey->fds[i][j];
                //printf("%c",findkey->isolationfd[i][sw][w]);
                w++;
                
            }
        }
        //printf("\n");
    }
    //return findkey->isolationfd;
    
}

void laplace(char* relation)
{
    /*
    system("touch log");
    system("clear");
    */  
    FILE * file;
    file = fopen("log","a");
    if(file == NULL)
    {
        system("clear");
        printf("Segmentation fault\n");
        exit(EXIT_SUCCESS);
    }
    char input[200];
    char **temp ;
    char r[100];
    //scanf("%s",input);
    scanf("%s",r);
    int x= atoi(r);
    temp = calloc(x+2,sizeof(char*));
    int i;
    for( i = 0 ; i < x+2 ; i++)
    {
        temp[i]=calloc(200,sizeof(char));
    }
    strcpy(temp[0],relation);
    strcpy(temp[1],r);
    for( i = 2 ; i < x+2; i++)
    {
        scanf("%s",temp[i]);
    }
/*
    for(int i = 0 ; i < x+2 ;i++ )
    {
        printf("%s\n",temp[i]);
    }
*/  
    char * t;
    int tmp=0;
    t= calloc((x+2)*200,sizeof(char));
    for( i = 0 ; i < x+2 ; i++)
    {
        strncat(t,temp[i],strlen(temp[i]));
        tmp = tmp+ strlen(temp[i]);
        strncat(t,"\n",2);
    }
    strncat(t,"\n",2);
    //printf("%s",t);
    fputs(t,file);
    fclose(file);
    FILE * file2=fopen("log","r");
    if(file2 ==NULL)
    {
        system("clear");
        printf("Segmentation fault\n");
        exit(EXIT_SUCCESS);
    }
    system("db.compose < log ");
    system("rm log");
    exit(EXIT_SUCCESS);
}
 
/**
 * To remove schema's name and parentheses and return the string
 * @param relation The input schema
 */
void* getword(char* relation)
{
    laplace(relation);
    int i , j ;
    char* temp = calloc(strlen(relation),sizeof(char));
    for(  i = 0 ; i < strlen(relation) ; i ++ )
    {
        if(relation[i] == '(')
        {
            for(  j = i+1 ; j < strlen(relation)-1 ; j++ )
            {
                temp[j-(i+1)]=relation[j];
            }
            break;
        }
    }
    return strcpy(relation,temp);
}













//------------------------Math----------------
int s(int n)
{
    int result=1,i;
    for( i = 1 ; i <= n ; i++) result = i*result;
    return result;
}
int c(int n,int r)
{
    return s(n) / ( s(r)*s(n-r));  
}
/**
 * Calculate the number of all closure
 */
int TotalR(int t)
{
    int a=0,i;
    for( i = 1 ; i <= t ; i ++) a = a + c(t,i);
    return a; 
}