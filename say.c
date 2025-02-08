#include<stdio.h>
#include <stdlib.h>

FILE *words_data_filep;
const int WORDS_LENGTH = 30;
int words_width_data[WORDS_LENGTH];
//FILE *words;
const int SPACE_POS = 105;
const int SPACE_WIDTH_POS = 26;
const int MAX_WIDTH = 150;

struct chardata {
    char c;
    int pos;
    int width;
};
struct linkedlist {
    struct chardata curr;
    struct linkedlist *next;
};

struct chardata fetch(char c) {
    struct chardata curr = { .c = '\0', .pos = SPACE_POS, .width = 0 };
    if (c >= 'a' && c <= 'z') 
    {
        curr.c = c - 'a' + 'A';
        curr.pos = (c - 'a') * 4 + 1;
        curr.width = words_width_data[(c - 'a')];
    }else if (c >= 'A' && c <= 'Z') 
    {
        curr.c = c;
        curr.pos = (c - 'A') * 4 + 1;
        curr.width = words_width_data[(c - 'A')];

    }else
    {
        curr.c = c;
        curr.pos = SPACE_POS;
        curr.width = words_width_data[SPACE_WIDTH_POS];
    }
    
    //fseek(words_data_filep, pos-1, SEEK_SET);
    return curr;
}
int init_files(void) {
    system("./lines.sh");
    words_data_filep = fopen("words_data.txt","r");
    //words = fopen("words.txt","r");
    if(words_data_filep == NULL){
        printf("cannot find words_data.txt\n");
        return 1;
    }
    // if(words == NULL){
    //     printf("cannot find words.txt");
    //     return 1;
    // }
    int i = 0;
    int tempint = 0;
    int scan_result = 0;
    char line[3];
    while(fgets(line, 2, words_data_filep)){
        if(sscanf(line, "%d", &tempint) != 1){
            continue;
        }
        words_width_data[i] = tempint;
        i++;
    }
    fclose(words_data_filep);
    //fclose(words);
    return 0;
}

int main(int argsc, char *argsv[]) {
    //printf("main start, %d arguments\n", argsc);
    if (init_files() != 0){
        return EXIT_FAILURE;
    }
    //printf("inited data \n");
    const char *arg;
    //system("echo './say.sh' > temp.txt");
    struct chardata curr_char;
    int curr_width = 0;
    char tempstr[10];
    for(int i = 1; i < argsc; i++){
        //printf("%s:%c\n",argsv[i],*argsv[i]);
        arg = argsv[i];
        while(*arg != '\0'){
            curr_char = fetch(*arg);
            curr_width += curr_char.width;
            printf("%d ", curr_char.pos);
            if(curr_width >= MAX_WIDTH){
                curr_width = 0;
                printf("\n");
            }
            
            arg++;
        }
        curr_char = fetch(' ');
        curr_width += curr_char.width;
        printf("%d ", curr_char.pos);
        //printf("(char:%c,pos:%d,width:%d)\n", *arg, curr_char.pos, curr_char.width);
        if(curr_width >= MAX_WIDTH){
            curr_width = 0;
            printf("\n");
        }
    }
    printf("\n");
    //printf("\nend of program\n");

}