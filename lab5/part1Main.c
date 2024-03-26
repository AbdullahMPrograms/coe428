#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

extern char* pop();
extern void push(char*);
extern int isEmpty();

int main(int argc, char* argv[]) {
    int ch;
    char tag[100];
    int index = 0;
    int isStartTag = 0;

    while ((ch = getchar()) != EOF) {
        if (ch == '<') {
            //check next character to see if it is a start tag or end tag
            if ((ch = getchar()) == '/') {
                isStartTag = 0;
            } else {
                //if not an end tag, put the character back into the input stream
                ungetc(ch, stdin);
                isStartTag = 1;
            }
            index = 0;
            //read the tag until the next '>'
            while ((ch = getchar()) != '>' && ch != EOF) {
                tag[index++] = ch;
            }
            tag[index] = '\0';

            //check if the tag is valid
            if (isStartTag) {
                //push duplicate of tag into stack
                push(strdup(tag));
            } else {
                // if stack is empty, there are unmatched end tags
                if (isEmpty()) {
                    printf("Invalid XML: Unmatched end-tag </%s>\n", tag);
                    exit(1);
                }
                char* startTag = pop();
                //check if the start tag matches the end tag
                if (strcmp(startTag, tag) != 0) {
                    printf("Invalid XML: Mismatched tags <%s> and </%s>\n", startTag, tag);
                    exit(1);
                }
                free(startTag);
            }
        }
    }
    // if stack is not empty, there are unmatched start tags
    if (!isEmpty()) {
        printf("Invalid XML: Unmatched start-tag <%s>\n", pop());
        exit(1);
    }

    printf("Valid XML\n");
    exit(0);
}