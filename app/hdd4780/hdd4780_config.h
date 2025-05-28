#ifndef HDD4780_HDD4780_CONFIG_H
#define HDD4780_HDD4780_CONFIG_H

#include "hdd4780_commands.h"
#include <stddef.h>
#include <stdint.h>

#define HDD4780_DEVICE_ADDRESS 0x27

#define HDD4780_LINE_WIDTH 16U * 5U
#define HDD4780_LINE_HEIGHT 8U
#define HDD4780_NUM_LINES 2U

#define HDD4780_FRAME_BUF_SIZE (HDD4780_NUM_LINES * HDD4780_LINE_WIDTH * HDD4780_LINE_HEIGHT / 8U)

typedef enum {
    HDD4780_ERR_OK = 0,
    HDD4780_ERR_FAIL = 1 << 0,
    HDD4780_ERR_NULL = 1 << 1,
} hdd4780_err_t;

typedef enum {
    HDD4780_ID_INCREMENT = 0x01,
    HDD4780_ID_DECREMENT = 0x00,
} hdd4780_id_t;

typedef enum {
    HDD4780_SC_DISPLAY_SHIFT = 0x01,
    HDD4780_SC_CURSOR_MOVE = 0x00,
} hdd4780_sc_t;

typedef enum {
    HDD4780_RL_SHIFT_RIGHT = 0x01,
    HDD4780_RL_SHIFT_LEFT = 0x00,
} hdd4780_rl_t;

typedef enum {
    HDD4780_DL_BITS_8 = 0x01,
    HDD4780_DL_BITS_4 = 0x00,
} hdd4780_dl_t;

typedef enum {
    HDD4780_N_LINES_2 = 0x01,
    HDD4780_N_LINES_1 = 0x00,
} hdd4780_n_t;

typedef enum {
    HDD4780_F_DOTS_5x10 = 0x01,
    HDD4780_F_DOTS_5x8 = 0x00,
} hdd4780_f_t;

typedef enum {
    HDD4780_BF_INTERNALLY_OPERATING = 0x01,
    HDD4780_BF_INSTRUCTIONS_ACCEPTABLE = 0x00,
} hdd4780_bf_t;

typedef struct {
    uint8_t char_height;
    uint8_t char_width;
    uint8_t* font_bitmap;
} hdd4780_config_t;

typedef struct {
    void* bus_user;
    hdd4780_err_t (*bus_init)(void*);
    hdd4780_err_t (*bus_deinit)(void*);
    hdd4780_err_t (*bus_transmit)(void*, uint8_t const*, size_t);
} hdd4780_interface_t;

#endif // HDD4780_HDD4780_CONFIG_H