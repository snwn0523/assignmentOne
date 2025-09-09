#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 26

int used[N];
int par[N];
int chil[N][N];

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        return EXIT_FAILURE;
    }

    FILE * fptr = fopen(argv[1], "r");
    if(fptr == NULL)
    {
        return EXIT_FAILURE;
    }

    for(int i = 0; i < N; i++)
    {
        used[i] = 0;
        par[i] = -1;
        for(int j = 0; j < N; j++)
        {
            chil[i][j] = 0;
        }
    }

    char line[128];
    while(fgets(line, sizeof(line), fptr))
    {
        line[strcspn(line, "\r\n")] = '\0';

        if(strlen(line) != 2)
        {
            printf("INVALID\n");
            fclose(fptr);
            return EXIT_FAILURE;
        }

        int pari = line[0] - 'A';
        int chili = line[1] - 'A';

        used[pari] = 1;
        used[chili] = 1;
        par[chili] = pari;
        chil[pari][chili] = 1;
    }

    fclose(fptr);

    int root[N];
    int rootlen = 0;
    
    for(int i = 0; i < N; i++)
    {
        if(used[i] && par[i] == -1)
        {
            root[rootlen++] = i;
        }
    }

    for(int i = 0; i < rootlen; i++)
    {
        putchar('A' + root[i]);
        putchar('\n');

        int cur[26];
        int curlen = 0;
        cur[curlen++] = root[i];

        while(1)
        {
            int next[26];
            int nextlen = 0;
            int allsharp = 1;

            for(int i = 0; i < curlen; i++)
            {
                if(i > 0)
                {
                    putchar(' ');
                }

                int p = cur[i];
                int hasChild = 0;

                for(int j = 0; j < N; j++)
                {
                    if(chil[p][j])
                    {
                        hasChild = 1;
                        allsharp = 0;
                        putchar('A' + j);
                        next[nextlen++] = j;
                    }
                }
                if(hasChild == 0)
                {
                    putchar('#');
                }
            }
            putchar('\n');

            if(allsharp == 1)
            {
                break;
            }

            curlen = nextlen;
            for(int i = 0; i < nextlen; i++)
            {
                cur[i] = next[i];
            }
        }
        putchar('\n');
    }
    return EXIT_SUCCESS;
}



