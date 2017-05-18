#include <limits.h>
#include "gtest/gtest.h"
#include "tool.h"
#include "ont_edp_private.h"

TEST(AckTest, Normal){
    uint16_t msg_id = 1;

    //gen by edp protocol tool with device id and auth info above
    const char data[] = { 0X40,0X00,0X01,0X00 };

    EXPECT_EQ(msg_id, ont_edp_handle_save_ack((const unsigned char*)data, sizeof(data)));
}

