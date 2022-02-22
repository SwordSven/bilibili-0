#include <stdio.h>
#include <string.h>
#include "ringbuff.h"

static char main_buf[14];

int main(void) {
    struct ringbuff my_ringbuff = {
        main_buf,
        sizeof(main_buf),
        0, 0, 0, 0
    };

    const char * msg = "Hello world";

    int i = 2;
    while(i--) {

        for(int i = 0; i < strlen(msg); i++) {
            ringbuff_putchar(&my_ringbuff, msg[i]);
        }
        
        ringbuff_debug(&my_ringbuff);

        char str[14];

        for(int i = 0; i < strlen(msg); i++) {
            ringbuff_getchar(&my_ringbuff, &((uint8_t *)str)[i]);
        }

        printf("str = %s\n", str);

        ringbuff_debug(&my_ringbuff);

    }
}