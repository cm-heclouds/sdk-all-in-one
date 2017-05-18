#include <limits.h>
#include "gtest/gtest.h"
#include "tool.h"
#include "ont_edp_private.h"

TEST(CmdTest, Normal){
    ont_edp_device_t device;
    ont_device_cmd_t *cmd = NULL;

    device.cmd = ont_list_create();

    device.info.formatter =
        (ont_pkt_formatter_t*)ont_platform_malloc(sizeof(ont_pkt_formatter_t));
    ont_pkt_formatter_init(device.info.formatter);

    const char cmd_id[] = "80c199e2-7da1-596f-aa02-1a5a4e0edc6b";
    const char bin[] = { 0X31, 0X32, 0X33, 0X34, 0X35, 0X36, 0X37 };

    //gen by edp protocol tool with device id and auth info above
    const char data[] = { 0X00, 0X24, 0X38, 0X30, 0X63, 0X31, //0XA0, 0X31, 
                          0X39, 0X39, 0X65, 0X32, 0X2D, 0X37, 0X64, 0X61, 
                          0X31, 0X2D, 0X35, 0X39, 0X36, 0X66, 0X2D, 0X61, 
                          0X61, 0X30, 0X32, 0X2D, 0X31, 0X61, 0X35, 0X61, 
                          0X34, 0X65, 0X30, 0X65, 0X64, 0X63, 0X36, 0X62, 
                          0X00, 0X00, 0X00, 0X07, 0X31, 0X32, 0X33, 0X34, 
                          0X35, 0X36, 0X37};

    ASSERT_TRUE(0 == ont_edp_handle_get_cmd((const unsigned char*)data, sizeof(data), &device));

    ont_list_pop_front(device.cmd, (void **)&cmd);

    printf("correct  cmd id:%s\n", cmd_id);
    printf("unpacked cmd id:%s\n", cmd->id);

    EXPECT_TRUE(!strcmp(cmd_id, cmd->id));

    Tool::Dump("correct data", bin, sizeof(bin));
    Tool::Dump("packed data", cmd->req, cmd->size);;

    EXPECT_TRUE(cmd->size == sizeof(bin)
        && !memcmp(bin, cmd->req, sizeof(bin)));
}


