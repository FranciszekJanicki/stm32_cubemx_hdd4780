#ifndef HDD4780_HDD4780_H
#define HDD4780_HDD4780_H

#include "hdd4780_commands.h"
#include "hdd4780_config.h"
#include <stdint.h>

typedef struct {
    hdd4780_config_t config;
    hdd4780_interface_t interface;

    uint8_t frame_buf[HDD4780_FRAME_BUF_SIZE];
} hdd4780_t;

hdd4780_err_t
hdd4780_initialize(hdd4780_t* hdd4780, hdd4780_config_t const* config, hdd4780_interface_t const* interface);
hdd4780_err_t hdd4780_deinitialize(hdd4780_t* hdd4780);

hdd4780_err_t hdd4780_display_frame_buf(hdd4780_t* hdd4780);
void hdd4780_clear_frame_buf(hdd4780_t* hdd4780);

hdd4780_err_t hdd4780_send_clear_display_cmd(hdd4780_t const* hdd4780);

hdd4780_err_t hdd4780_send_return_home_cmd(hdd4780_t const* hdd4780);

hdd4780_err_t hdd4780_send_entry_mode_set_cmd(hdd4780_t const* hdd4780, uint8_t id, uint8_t s);

hdd4780_err_t hdd4780_send_display_on_off_control_cmd(hdd4780_t const* hdd4780, uint8_t d, uint8_t c, uint8_t b);

hdd4780_err_t hdd4780_send_cursor_or_display_shift_cmd(hdd4780_t const* hdd4780, uint8_t sc, uint8_t rl);

hdd4780_err_t hdd4780_send_function_set_cmd(hdd4780_t const* hdd4780, uint8_t dl, uint8_t n, uint8_t f);

hdd4780_err_t hdd4780_send_set_cgram_address_cmd(hdd4780_t const* hdd4780, uint8_t acg);

hdd4780_err_t hdd4780_send_set_ddram_address_cmd(hdd4780_t const* hdd4780, uint8_t add);

hdd4780_err_t hdd4780_send_read_busy_flag_cmd(hdd4780_t const* hdd4780, uint8_t bf, uint8_t ac);

#endif // HDD4780_HDD4780_H