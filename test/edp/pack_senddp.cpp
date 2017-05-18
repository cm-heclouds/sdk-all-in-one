#include <limits.h>
#include "gtest/gtest.h"
#include "tool.h"
#include "ont_edp_private.h"

TEST(SendDPTest, NoMsgID){
    ont_edp_device_t device;

    device.info.formatter =
        (ont_pkt_formatter_t*)ont_platform_malloc(sizeof(ont_pkt_formatter_t));
    ont_pkt_formatter_init(device.info.formatter);

    const char bin[] = "123";
    short msg_id = 0;
    ont_edp_handle_send_dp(&device, bin, sizeof(bin), msg_id);

    //gen by edp protocol tool with device id and auth info above
    const unsigned char data[] = { 0X80, 0X05, 0x00, 0x31, 0x32, 0x33, 0x00};

    Tool::Dump("packet data", (const char*)data, sizeof(data));
    Tool::Dump("correct data", device.info.formatter->result.data, device.info.formatter->result.len);

    EXPECT_TRUE(device.info.formatter->result.len == sizeof(data)
        && !memcmp(device.info.formatter->result.data, data, device.info.formatter->result.len));
}

TEST(SendDPTest, MsgID){
    ont_edp_device_t device;

    device.info.formatter =
        (ont_pkt_formatter_t*)ont_platform_malloc(sizeof(ont_pkt_formatter_t));
    ont_pkt_formatter_init(device.info.formatter);

    const char bin[] = "123";
    short msg_id = 11;
    ont_edp_handle_send_dp(&device, bin, sizeof(bin), msg_id);

    //gen by edp protocol tool with device id and auth info above
    const unsigned char data[] = { 0X80, 0X07, 0x40, 0x00, 0x0B, 0x31, 0x32, 0x33, 0x00 };

    Tool::Dump("packet data", (const char*)data, sizeof(data));
    Tool::Dump("correct data", device.info.formatter->result.data, device.info.formatter->result.len);

    EXPECT_TRUE(device.info.formatter->result.len == sizeof(data)
        && !memcmp(device.info.formatter->result.data, data, device.info.formatter->result.len));
}
