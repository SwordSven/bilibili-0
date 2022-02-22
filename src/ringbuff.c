#include "ringbuff.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

int16_t ringbuff_data_len(ringbuff_t p_rb) {
    switch (ringbuff_state_get(p_rb))
    {
    case RINGBUFF_EMPTY:
        return 0;
    case RINGBUFF_FULL:
        return p_rb->size;
    case RINGBUFF_HALFFULL:
        if(p_rb->read_mirror == p_rb->write_mirror) {
            return p_rb->write_pos - p_rb->read_pos;
        } else {
            return p_rb->size - (p_rb->read_pos - p_rb->write_pos);
        }
    }

    // never reach here
    return p_rb->size;
};

int32_t ringbuff_getchar(ringbuff_t p_rb, uint8_t * ch) {
    assert(p_rb != NULL);

    if(!ringbuff_data_len(p_rb)) {
        // empty buffer
        return 0;
    }

    *ch = ((char*)p_rb->buf)[p_rb->read_pos];

    if(p_rb->read_pos == p_rb->size - 1) {
        p_rb->read_mirror = ~p_rb->read_mirror;
        p_rb->read_pos = 0;
    } else {
        p_rb->read_pos++;
    }

    return 1;
};

int32_t ringbuff_putchar(ringbuff_t p_rb, const uint8_t ch) {
    assert(p_rb != NULL);

    if(!ringbuff_data_space_len(p_rb)) {
        // full buffer
        return 0;
    }

    ((char*)p_rb->buf)[p_rb->write_pos] = ch;

    if(p_rb->write_pos == p_rb->size - 1) {
        p_rb->write_mirror = ~p_rb->write_mirror;
        p_rb->write_pos = 0;
    } else {
        p_rb->write_pos++;
    }

    return 1;
};

int32_t ringbuff_peekchar(ringbuff_t p_rb, uint8_t * ch) {
    assert(p_rb != NULL);

    if(!ringbuff_data_len(p_rb)) {
        // empty buffer
        return 0;
    }

    *ch = ((char*)p_rb->buf)[p_rb->read_pos];

    return 1;
};

void ringbuff_debug(ringbuff_t p_rb) {
    printf("---ringbuff debug---\n");
    printf("ringbuff buf:\n");
    for(int i = 0; i < p_rb->size; i++) {
        printf("%c", ((char*)p_rb->buf)[i]);
    }
    printf("\n");
    printf("ringbuff buf end---\n");
    printf("read_mirror = %d\n", p_rb->read_mirror);
    printf("read_pos = %d\n", p_rb->read_pos);
    printf("write_mirror = %d\n", p_rb->write_mirror);
    printf("write_pos = %d\n", p_rb->write_pos);
    printf("---ringbuff debug end---\n");
}