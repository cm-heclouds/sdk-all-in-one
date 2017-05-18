#include <limits.h>
#include "gtest/gtest.h"
#include "tool.h"
#include "ont_edp_private.h"

TEST(ReplyCmdTest, Normal){
    ont_edp_device_t device;

    device.info.formatter =
        (ont_pkt_formatter_t*)ont_platform_malloc(sizeof(ont_pkt_formatter_t));
    ont_pkt_formatter_init(device.info.formatter);

    const char cmd_id[] = "80c199e2-7da1-596f-aa02-1a5a4e0edc6b";
    const char bin[] = { 0X31, 0X32, 0X33, 0X34, 0X35, 0X36, 0X37 };
    ont_edp_handle_reply_cmd(&device, cmd_id, bin, sizeof(bin));

    //gen by edp protocol tool with device id and auth info above
    const unsigned char data[] = { 0XB0, 0X31, 0X00, 0X24, 0X38, 0X30, 0X63, 0X31, 0X39, 0X39, 0X65, 0X32, 0X2D, 0X37, 0X64, 0X61, 0X31, 0X2D, 0X35, 0X39, 0X36, 0X66, 0X2D, 0X61, 0X61, 0X30, 0X32, 0X2D, 0X31, 0X61, 0X35, 0X61, 0X34, 0X65, 0X30, 0X65, 0X64, 0X63, 0X36, 0X62, 0X00, 0X00, 0X00, 0X07, 0X31, 0X32, 0X33, 0X34, 0X35, 0X36, 0X37, };

    Tool::Dump("correct data", (const char* )data, sizeof(data));
    Tool::Dump("packed data", device.info.formatter->result.data, device.info.formatter->result.len);

    EXPECT_TRUE(device.info.formatter->result.len == sizeof(data)
        && !memcmp(device.info.formatter->result.data, data, device.info.formatter->result.len));
}

