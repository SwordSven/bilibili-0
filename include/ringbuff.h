#ifndef _RINGBUFF_
#define _RINGBUFF_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>

struct ringbuff {
    void * buf;
    int16_t size;       //buf 最大 32KB

    uint16_t read_mirror: 1;
    uint16_t read_pos: 15;
    uint16_t write_mirror: 1;
    uint16_t write_pos: 15;
};
typedef struct ringbuff * ringbuff_t;

#define RINGBUFF_EMPTY      0
#define RINGBUFF_FULL       1
#define RINGBUFF_HALFFULL   2

static inline int32_t ringbuff_state_get(ringbuff_t p_rb) {
    if(p_rb->read_pos == p_rb->write_pos) {
        if(p_rb->read_mirror == p_rb->write_mirror)
            return RINGBUFF_EMPTY;
        else
            return RINGBUFF_FULL;
    }
    else 
        return RINGBUFF_HALFFULL;
}

#define ringbuff_data_space_len(p_rb) ((p_rb)->size - ringbuff_data_len(p_rb))

int16_t ringbuff_data_len(ringbuff_t p_rb);
int32_t ringbuff_getchar(ringbuff_t p_rb, uint8_t * ch);
int32_t ringbuff_putchar(ringbuff_t p_rb, const uint8_t ch);

void ringbuff_debug(ringbuff_t p_rb);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _RINGBUFF_ */