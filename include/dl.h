#ifndef __LIBDRAGON_DL_H
#define __LIBDRAGON_DL_H

#include <stdint.h>
#include <rsp.h>

typedef struct dl_block_s dl_block_t;

void dl_init();

void* dl_overlay_get_state(rsp_ucode_t *overlay_ucode);
uint8_t dl_overlay_add(rsp_ucode_t *overlay_ucode);
void dl_overlay_register_id(uint8_t overlay_index, uint8_t id);

void dl_start();
void dl_close();

#define dl_terminator(dl)   ({ *(uint8_t*)(dl) = 0x01; })

extern uint32_t *dl_cur_pointer;
extern uint32_t *dl_sentinel;

static inline uint32_t* dl_write_begin(void) {
    return dl_cur_pointer;
}

void dl_write_end(uint32_t *dl);

void dl_block_begin(void);
dl_block_t* dl_block_end(void);
void dl_block_free(dl_block_t *block);
void dl_block_run(dl_block_t *block);

int dl_syncpoint(void);
bool dl_check_syncpoint(int sync_id);
void dl_wait_syncpoint(int sync_id);

static inline void dl_sync() {
    dl_wait_syncpoint(dl_syncpoint());
}

void dl_queue_u8(uint8_t cmd);
void dl_queue_u16(uint16_t cmd);
void dl_queue_u32(uint32_t cmd);
void dl_queue_u64(uint64_t cmd);

void dl_noop();
void dl_signal(uint32_t signal);

#endif
