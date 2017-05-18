#define GTEST_USE_OWN_TR1_TUPLE 0
#include <gtest/gtest.h>
#include "parser/macros.h"
#include "parser/ont_pkt_formatter.h"
#include "ont/error.h"

class FormatterTest : public testing::Test {
protected:
    // TestSuite
    static void SetUpTestCase() {
    }

    static void TearDownTestCase() {
    }

    // TestCase
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};


ont_parser_def_packet_begin(edp_connect_t)
ont_parser_add_elem(pro, bytes)
ont_parser_add_elem(ver, uint8)
ont_parser_add_elem(flag, uint8)
ont_parser_add_elem(keepalive, uint16)
ont_parser_add_elem(dev_id, bytes)
ont_parser_add_elem(user_id, bytes)
ont_parser_add_elem(auth_info, bytes)
ont_parser_def_packet_end(edp_connect_t)

ont_parser_def_packet_begin(edp_save_data_t)
ont_parser_add_elem(flag, uint8)
ont_parser_add_elem(dst, bytes)
ont_parser_add_elem(msg_id, uint16)
ont_parser_def_packet_end(edp_save_data_t)

static int32_t edp_user_id_filter(ont_parser_list_node_t* node){
    ont_parser_uint8_t* p = (ont_parser_uint8_t*)node;
    if (p->value & 0x80){
        return 0;
    }

    return 1;
}

ont_parser_init_begin(edp_connect_t, pro, bytes)
ont_parser_queue_up(ver, uint8, NULL, none);
ont_parser_queue_up(flag, uint8, NULL, none);
ont_parser_queue_up(keepalive, uint16, NULL, none);
ont_parser_queue_up(dev_id, bytes, NULL, none);
ont_parser_queue_up(user_id, bytes, edp_user_id_filter, flag);
ont_parser_queue_up(auth_info, bytes, NULL, none);
ont_parser_init_end()

TEST_F(FormatterTest, FormatterTestSerialize){
    ont_pkt_formatter_t formatter;
    EXPECT_EQ(ont_pkt_formatter_init(&formatter), ONT_ERR_OK);

    edp_connect_t pkt;
    ont_parser_init_edp_connect_t(&pkt);
    uint8_t s_buf[] = {0x1, 0x13, 0x0, 0x3, 0x45, 0x44, 0x50, 0x1, 0x40, 0x0, 0x2, 0x0, 0x3, 0x61, 0x61, 0x61, 0x0, 0x3, 0x62, 0x62, 0x62};
    pkt.pro.value = "EDP";
    pkt.pro.len = 3;
    pkt.ver.value = 1;
    pkt.flag.value |= 0x40;
    pkt.keepalive.value = 2;
    pkt.dev_id.value = (char*)"aaa";
    pkt.dev_id.len = 3;
    pkt.auth_info.value = (char*)"bbb";
    pkt.auth_info.len = 3;

    ont_pkt_serialize_finish(&formatter, 1, &pkt.head);
    EXPECT_EQ(memcmp(formatter.result.data, s_buf, 21), 0);

}


TEST_F(FormatterTest, FormatterTestAddUint32){
    ont_pkt_formatter_t formatter;
    uint8_t s_buf[] = {0x8, 0x0, 0x1, 0x1, 0x61, 0x62, 0x63, 0x0, 0x0, 0x0, 0x0, 0x1};
    EXPECT_EQ(ont_pkt_formatter_init(&formatter), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_uint32(&formatter, (char*)"abc", 1), ONT_ERR_OK);
    EXPECT_EQ(memcmp(formatter.result.data, s_buf, formatter.result.len), 0);
}

TEST_F(FormatterTest, FormatterTestAddDouble){
    ont_pkt_formatter_t formatter;
    uint8_t s_buf[] = {0x8, 0x0, 0x1, 0x2, 0x61, 0x62, 0x63, 0x0, 0x3f, 0xf3, 0xae, 0x14, 0x7a, 0xe1, 0x47, 0xae};
    EXPECT_EQ(ont_pkt_formatter_init(&formatter), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_double(&formatter, (char*)"abc", 1.23), ONT_ERR_OK);
    EXPECT_EQ(memcmp(formatter.result.data, s_buf, formatter.result.len), 0);
}

TEST_F(FormatterTest, FormatterTestAddString){
    ont_pkt_formatter_t formatter;
    uint8_t s_buf[] = {0x8, 0x0, 0x1, 0x3, 0x61, 0x62, 0x63, 0x0, 0x61, 0x62, 0x63, 0x0};
    EXPECT_EQ(ont_pkt_formatter_init(&formatter), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_string(&formatter, (char*)"abc", (char*)"abc"), ONT_ERR_OK);
    EXPECT_EQ(memcmp(formatter.result.data, s_buf, formatter.result.len), 0);
}

TEST_F(FormatterTest, FormatterTestAddbinary){
    ont_pkt_formatter_t formatter;
    uint8_t s_buf[] = {0x8, 0x0, 0x1, 0x4, 0x61, 0x62, 0x63, 0x0, 0x0, 0x0, 0x0, 0x3, 0x61, 0x62, 0x63};
    EXPECT_EQ(ont_pkt_formatter_init(&formatter), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_binary(&formatter, (char*)"abc", (char*)"abc", 3), ONT_ERR_OK);
    EXPECT_EQ(memcmp(formatter.result.data, s_buf, formatter.result.len), 0);
}

TEST_F(FormatterTest, FormatterTestJson){
    ont_pkt_formatter_t formatter;
    uint8_t s_buf[] = {0x8, 0x0, 0x1, 0x5, 0x61, 0x62, 0x63, 0x0, 0x7b, 0x61, 0x3a, 0x62, 0x7d, 0x0};
    EXPECT_EQ(ont_pkt_formatter_init(&formatter), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_json(&formatter, (char*)"abc", (char*)"{a:b}"), ONT_ERR_OK);
    EXPECT_EQ(memcmp(formatter.result.data, s_buf, formatter.result.len), 0);
}


TEST_F(FormatterTest, FormatterTestAll){
    ont_pkt_formatter_t formatter;
    uint8_t s_buf[] = {0x8, 0x0, 0x5, 0x1, 0x61, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x62, 0x0, 0x3f, 0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3, 0x63, 0x0, 0x61, 0x61, 0x61, 0x0, 0x4, 0x64, 0x0, 0x0, 0x0, 0x0, 0x3, 0x62, 0x62, 0x62, 0x5, 0x65, 0x0, 0x7b, 0x61, 0x3a, 0x62, 0x7d, 0x0};
    EXPECT_EQ(ont_pkt_formatter_init(&formatter), ONT_ERR_OK);

    EXPECT_EQ(ont_pkt_formatter_add_uint32(&formatter, (char*)"a", 1), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_double(&formatter, (char*)"b", 1.2), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_string(&formatter, (char*)"c", (char*)"aaa"), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_binary(&formatter, (char*)"d", (char*)"bbb", 3), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_json(&formatter, (char*)"e", (char*)"{a:b}"), ONT_ERR_OK);
    EXPECT_EQ(memcmp(formatter.result.data, s_buf, formatter.result.len), 0);

    ont_pkt_formatter_reset(&formatter, 0);
    EXPECT_EQ(ont_pkt_formatter_add_uint32(&formatter, (char*)"a", 1), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_double(&formatter, (char*)"b", 1.2), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_string(&formatter, (char*)"c", (char*)"aaa"), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_binary(&formatter, (char*)"d", (char*)"bbb", 3), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_json(&formatter, (char*)"e", (char*)"{a:b}"), ONT_ERR_OK);
    EXPECT_EQ(memcmp(formatter.result.data, s_buf, formatter.result.len), 0);

    ont_pkt_formatter_reset(&formatter, 1);
    EXPECT_EQ(ont_pkt_formatter_add_uint32(&formatter, (char*)"a", 1), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_double(&formatter, (char*)"b", 1.2), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_string(&formatter, (char*)"c", (char*)"aaa"), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_binary(&formatter, (char*)"d", (char*)"bbb", 3), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_json(&formatter, (char*)"e", (char*)"{a:b}"), ONT_ERR_OK);
    EXPECT_EQ(memcmp(formatter.result.data, s_buf, formatter.result.len), 0);

    ont_pkt_formatter_destroy(&formatter);
    EXPECT_EQ(ont_pkt_formatter_add_uint32(&formatter, (char*)"a", 1), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_double(&formatter, (char*)"b", 1.2), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_string(&formatter, (char*)"c", (char*)"aaa"), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_binary(&formatter, (char*)"d", (char*)"bbb", 3), ONT_ERR_OK);
    EXPECT_EQ(ont_pkt_formatter_add_json(&formatter, (char*)"e", (char*)"{a:b}"), ONT_ERR_OK);
    EXPECT_EQ(memcmp(formatter.result.data, s_buf, formatter.result.len), 0);
}
