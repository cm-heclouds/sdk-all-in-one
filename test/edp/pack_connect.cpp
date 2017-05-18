#include <limits.h>
#include "gtest/gtest.h"
#include "tool.h"
#include "ont_edp_private.h"

TEST(ConnectTest, Normal){
    const char* auth_info = "x108ijlfdsua883";
    ont_edp_device_t device;

    device.info.device_id = 12345;
    device.info.keepalive = 300;
    device.info.formatter =
        (ont_pkt_formatter_t*)ont_platform_malloc(sizeof(ont_pkt_formatter_t));
    ont_pkt_formatter_init(device.info.formatter);

    ont_edp_handle_connect(&device, auth_info);

    //gen by edp protocol tool with device id and auth info above
    const char data[] = { 0X10, 0X21, 0X00, 0X03, 0X45, 0X44, 0X50, 
                          0X01, 0X40, 0X01, 0X2C, 0X00, 0X05, 0X31, 
                          0X32, 0X33, 0X34, 0X35, 0X00, 0X0F, 0X78, 
                          0X31, 0X30, 0X38, 0X69, 0X6A, 0X6C, 0X66, 
                          0X64, 0X73, 0X75, 0X61, 0X38, 0X38, 0X33 };

    Tool::Dump("packet data", data, sizeof(data));
    Tool::Dump("correct data", device.info.formatter->result.data, device.info.formatter->result.len);

    EXPECT_TRUE(device.info.formatter->result.len == sizeof(data)
        && !memcmp(device.info.formatter->result.data, data, device.info.formatter->result.len));
}

