#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    printf("\n\n\n");
    printf("*********************** Shell Project **********************\n");
    printf("*********** Made by : Abedalkarim M. Aldabash ***************\n");
    printf("\n");
    while (1)
    {
        char path[100];
        getcwd(path, 100);
        printf("%s%s%s%s%s%s%s", "\e[1;31m", getenv("USER"), ":~", "\033[0m", path, "\033[0;32m", "$ " );
        //colors from "https://www.theurbanpenguin.com/4184-2/"


        char line[100] = {0};
        int fillindex = 0;
        char ch;
        scanf("%c", &ch);
        while (ch != '\n')
        {
            line[fillindex] = ch;
            fillindex++;
            scanf("%c", &ch);
        }

        char line2[100] = {0};
        strcpy(line2, line);

        char *prog = strtok(line2, " ");
        char *argvx[100];
        char *argtoken = prog;
        int index = 0;
        while (argtoken != NULL)
        {
            argvx[index] = argtoken;
            index++;
            argtoken = strtok(NULL, " ");
        }
        argvx[index] = NULL;

        if (prog == NULL)
        {
            continue;
        }

        if (strcmp(argvx[0], "pause") == 0)
        {
            char click = 0;
            printf("Enter Enter so you can Enter commands");
            while (click != '\n')
            {
                scanf("%c", &click);
            }
            continue;
        }

        if (strcmp(argvx[0], "quit") == 0)
        {
            exit(0);
        }

        if (strcmp(argvx[0], "cd") == 0)
        {
            char curr_path[1000];
            getcwd(curr_path, 1000);
            char newpath[1000];
            char *buffer;
            if (argvx[1][0] != '/')
            {
                strcpy(curr_path, strcat(curr_path, "/"));
            }
            strcpy(newpath, strcat(curr_path, argvx[1]));
            if (chdir(newpath) != 0)
            {
                printf("no such file or directory\n");
                continue;
            }

            continue;
        }

        if (strcmp(prog, "dir") == 0)
        {
            strcpy(argvx[0], "ls");
            pid_t p = fork();
            if (p == 0)
            {
                execvp("ls", argvx);
            }
            else
            {
                wait(NULL);
            }
            continue;
        }

        if (strcmp(argvx[0], "clr") == 0)
        {
            strcpy(argvx[0], "clear");
            pid_t p = fork();
            if (p == 0)
            {
                execvp("clear", argvx);
            }
            else
            {
                wait(NULL);
            }
            continue;
        }

        if (strcmp(argvx[0], "environ") == 0)
        {
            strcpy(argvx[0], "env");
            pid_t p = fork();
            if (p == 0)
            {
                execvp("env", argvx);
            }
            else
            {
                wait(NULL);
            }
            continue;
        }

        if (strcmp(argvx[0], "help") == 0)
        {
            pid_t p = fork();
            if (p == 0)
            {
                execlp("more", "more", "helpfile.txt", NULL);
            }
            else
            {
                wait(NULL);
            }
            continue;
        }
        int gpip_index = -1;
        int gpip_word_index = -1;
        int indexx2 = 0;
        while (argvx[indexx2] != 0)
        {
            if (strcmp(argvx[indexx2], ">") == 0)
            {
                gpip_index = indexx2;
            }
            if (strstr(argvx[indexx2], ">") != 0)
            {
                gpip_word_index = indexx2;
            }
            indexx2++;
        }
        char* befor_g;
        char* after_g; 
        
        if (gpip_word_index != -1)
        {
          char line3[100] = {0};

            strcpy(line3,line);
            befor_g =strtok(line3, ">");
            after_g = strtok(NULL, ">");

            char *befor_g2[100];
            char *argtoken =strtok(befor_g," ");
            int index = 0;
            while (argtoken != NULL)
            {
                befor_g2[index] = argtoken;
                index++;
                argtoken = strtok(NULL, " ");
            }
            befor_g2[index] = NULL;
            while (after_g[0] == ' ')
            {
                after_g++;
            }

            int file_des = open(after_g, O_RDWR | O_CREAT, 0777);
            int pid = fork();
            if (pid == 0)
            {
                dup2(file_des, 1);
                execvp(befor_g2[0], befor_g2);
                }
                else
                {
                    wait(0);
                }
                continue;
        }

        int and_index = -1;
        int index2 = 0;
        while (argvx[index2] != NULL)
        {
            if (strcmp(argvx[index2], "&") == 0 && argvx[index2+1]==NULL)
            {
                and_index = index2;
            }
            index2++;
        }
        if (and_index != -1)
            argvx[and_index] = NULL;
        pid_t forks = fork();

        if (forks == 0)
        {
            execvp(prog, argvx);
        }
        else
        {
            if (and_index == -1)
            {
                wait(NULL);
            }
            

        }




    }
}