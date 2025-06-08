#include "hdd4780.h"
#include <assert.h>
#include <string.h>

static hdd4780_err_t hdd4780_bus_init(hdd4780_t const* hdd4780)
{
    assert(hdd4780);

    if (hdd4780->interface.bus_init) {
        return hdd4780->interface.bus_init(hdd4780->interface.bus_user);
    }

    return HDD4780_ERR_NULL;
}

static hdd4780_err_t hdd4780_bus_deinit(hdd4780_t const* hdd4780)
{
    assert(hdd4780);

    if (hdd4780->interface.bus_deinit) {
        return hdd4780->interface.bus_deinit(hdd4780->interface.bus_user);
    }

    return HDD4780_ERR_NULL;
}

static hdd4780_err_t hdd4780_bus_transmit(hdd4780_t const* hdd4780,
                                          uint8_t const* transmit_data,
                                          size_t transmit_size)
{
    assert(hdd4780);

    if (hdd4780->interface.bus_transmit) {
        return hdd4780->interface.bus_transmit(hdd4780->interface.bus_user,
                                               transmit_data,
                                               transmit_size);
    }

    return HDD4780_ERR_NULL;
}

hdd4780_err_t hdd4780_initialize(hdd4780_t* hdd4780,
                                 hdd4780_config_t const* config,
                                 hdd4780_interface_t const* interface)
{
    assert(hdd4780);

    memset(hdd4780, 0, sizeof(*hdd4780));
    memcpy(&hdd4780->config, config, sizeof(*config));
    memcpy(&hdd4780->interface, interface, sizeof(*interface));

    return hdd4780_bus_init(hdd4780);
}

hdd4780_err_t hdd4780_deinitialize(hdd4780_t* hdd4780)
{
    assert(hdd4780);

    hdd4780_err_t err = hdd4780_bus_deinit(hdd4780);

    memset(hdd4780, 0, sizeof(*hdd4780));

    return err;
}

hdd4780_err_t hdd4780_display_frame_buf(hdd4780_t* hdd4780)
{
    assert(hdd4780);

    return hdd4780_bus_transmit(hdd4780, hdd4780->frame_buf, sizeof(hdd4780->frame_buf));
}

void hdd4780_clear_frame_buf(hdd4780_t* hdd4780)
{
    assert(hdd4780);

    memset(hdd4780->frame_buf, 0, sizeof(hdd4780->frame_buf));
}

hdd4780_err_t hdd4780_send_clear_display_cmd(hdd4780_t const* hdd4780)
{
    assert(hdd4780);

    uint8_t data = {};

    data |= HDD4780_CMD_CLEAR_DISPLAY;

    return hdd4780_bus_transmit(hdd4780, &data, sizeof(data));
}

hdd4780_err_t hdd4780_send_return_home_cmd(hdd4780_t const* hdd4780)
{
    assert(hdd4780);

    uint8_t data = {};

    data |= HDD4780_CMD_RETURN_HOME;

    return hdd4780_bus_transmit(hdd4780, &data, sizeof(data));
}

hdd4780_err_t hdd4780_send_entry_mode_set_cmd(hdd4780_t const* hdd4780, uint8_t id, uint8_t s)
{
    assert(hdd4780);

    uint8_t data = {};

    data |= HDD4780_CMD_ENTRY_MODE_SET;
    data |= (id & 0x01U) << 1U;
    data |= s & 0x01U;

    return hdd4780_bus_transmit(hdd4780, &data, sizeof(data));
}

hdd4780_err_t hdd4780_send_display_on_off_control_cmd(hdd4780_t const* hdd4780,
                                                      uint8_t d,
                                                      uint8_t c,
                                                      uint8_t b)
{
    assert(hdd4780);

    uint8_t data = {};

    data |= HDD4780_CMD_DISPLAY_ON_OFF_CONTROL;
    data |= (d & 0x01U) << 2U;
    data |= (c & 0x01U) << 1U;
    data |= b & 0x01U;

    return hdd4780_bus_transmit(hdd4780, &data, sizeof(data));
}

hdd4780_err_t hdd4780_send_cursor_or_display_shift_cmd(hdd4780_t const* hdd4780,
                                                       uint8_t sc,
                                                       uint8_t rl)
{
    assert(hdd4780);

    uint8_t data = {};

    data |= HDD4780_CMD_CURSOR_OR_DISPLAY_SHIFT;
    data |= (sc & 0x01U) << 3U;
    data |= (rl & 0x01U) << 2U;

    return hdd4780_bus_transmit(hdd4780, &data, sizeof(data));
}

hdd4780_err_t hdd4780_send_function_set_cmd(hdd4780_t const* hdd4780,
                                            uint8_t dl,
                                            uint8_t n,
                                            uint8_t f)
{
    assert(hdd4780);

    uint8_t data = {};

    data |= HDD4780_CMD_FUNCTION_SET;
    data |= (dl & 0x01U) << 4U;
    data |= (n & 0x01U) << 3U;
    data |= (f & 0x01U) << 2U;

    return hdd4780_bus_transmit(hdd4780, &data, sizeof(data));
}

hdd4780_err_t hdd4780_send_set_cgram_address_cmd(hdd4780_t const* hdd4780, uint8_t acg)
{
    assert(hdd4780);

    uint8_t data = {};

    data |= HDD4780_CMD_SET_CGRAM_ADDRESS;
    data |= acg & 0x3FU;

    return hdd4780_bus_transmit(hdd4780, &data, sizeof(data));
}

hdd4780_err_t hdd4780_send_set_ddram_address_cmd(hdd4780_t const* hdd4780, uint8_t add)
{
    assert(hdd4780);

    uint8_t data = {};

    data |= HDD4780_CMD_SET_DDRAM_ADDRESS;
    data |= add & 0x7FU;

    return hdd4780_bus_transmit(hdd4780, &data, sizeof(data));
}

hdd4780_err_t hdd4780_send_read_busy_flag_cmd(hdd4780_t const* hdd4780, uint8_t bf, uint8_t ac)
{
    assert(hdd4780);

    uint8_t data = {};

    data |= HDD4780_CMD_READ_BUSY_FLAG_AND_ADDRESS;
    data |= (bf & 0x01U) << 7U;
    data |= ac & 0x01U;

    return hdd4780_bus_transmit(hdd4780, &data, sizeof(data));
}
