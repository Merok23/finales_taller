#include <string.h>

int search(const char* string, const char* subString) {
    int len = strlen(string);
    int subLen = strlen(subString);
    int end = subLen;
    int start = 0;
    char buff[subLen + 1];
    int result = 0;
    buff[subLen] = "\0";
    for (int i = 0; i < len - subLen; i++) {
        memcpy(buff, string + start, subLen);
        if (strcmp(buff, subString) == 0) result++;
        end+=1;
        start+=1;
    }
    return result;
}