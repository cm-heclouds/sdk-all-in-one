#define GTEST_USE_OWN_TR1_TUPLE 0
#include <gtest/gtest.h>
#include "parser/macros.h"
#include "parser/parser.h"

class ParserTest : public testing::Test {
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

ont_parser_def_packet_begin(test_uint8)
ont_parser_add_elem(elem, uint8)
ont_parser_def_packet_end(test_uint8)

ont_parser_init_begin(test_uint8, elem, uint8)
ont_parser_init_end()


TEST_F(ParserTest, TestUint8){
    test_uint8 elem;
    test_uint8 elem2;
    char buf[100];
    size_t len = 0;
    memset(buf, 0, 100);

    EXPECT_EQ(ont_parser_init_test_uint8(&elem), ONT_ERR_OK);
    elem.elem.value = 8;

    EXPECT_EQ(ont_parser_len(&elem.head, &len), ONT_ERR_OK);
    EXPECT_EQ(len, 1);
    EXPECT_EQ(ont_parser_serialize(buf, 0, &elem.head), ONT_ERR_NOMEM);
    EXPECT_EQ(ont_parser_serialize(buf, 1, &elem.head), ONT_ERR_OK);
    EXPECT_EQ((uint8_t)buf[0],8);

    EXPECT_EQ(ont_parser_init_test_uint8(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 0, &elem2.head, 0), ONT_ERR_DESERIALIZE_INCOMPLETE);

    EXPECT_EQ(ont_parser_init_test_uint8(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 2, &elem2.head, 0), ONT_ERR_DESERIALIZE_DATA_LEFT);
    EXPECT_EQ(elem.elem.value, elem2.elem.value);

    EXPECT_EQ(ont_parser_init_test_uint8(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 1, &elem2.head, 0), ONT_ERR_OK);
}

ont_parser_def_packet_begin(test_uint16)
ont_parser_add_elem(elem, uint16)
ont_parser_def_packet_end(test_uint16)

ont_parser_init_begin(test_uint16, elem, uint16)
ont_parser_init_end()


TEST_F(ParserTest, TestUint16){
    test_uint16 elem;
    test_uint16 elem2;
    size_t len = 0;
    char buf[100];
    char value[] = {0x00, 0x10};
    memset(buf, 0, 100);

    EXPECT_EQ(ont_parser_init_test_uint16(&elem), ONT_ERR_OK);
    elem.elem.value = 16;

    EXPECT_EQ(ont_parser_len(&elem.head, &len), ONT_ERR_OK);
    EXPECT_EQ(len, 2);
    EXPECT_EQ(ont_parser_serialize(buf, 1, &elem.head), ONT_ERR_NOMEM);
    EXPECT_EQ(ont_parser_serialize(buf, 2, &elem.head), ONT_ERR_OK);
    EXPECT_EQ(strncmp(buf, value, 2), 0);

    EXPECT_EQ(ont_parser_init_test_uint16(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 1, &elem2.head, 0), ONT_ERR_DESERIALIZE_INCOMPLETE);

    EXPECT_EQ(ont_parser_init_test_uint16(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 4, &elem2.head, 0), ONT_ERR_DESERIALIZE_DATA_LEFT);

    EXPECT_EQ(ont_parser_init_test_uint16(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 2, &elem2.head, 0), ONT_ERR_OK);
    EXPECT_EQ(elem.elem.value, elem2.elem.value);
}

ont_parser_def_packet_begin(test_uint32)
ont_parser_add_elem(elem, uint32)
ont_parser_def_packet_end(test_uint32)

ont_parser_init_begin(test_uint32, elem, uint32)
ont_parser_init_end()


TEST_F(ParserTest, TestUint32){
    test_uint32 elem;
    test_uint32 elem2;
    size_t len = 0;
    char buf[100];
    char value[] = {0x00, 0x00, 0x00, 0x20};
    memset(buf, 0, 100);

    EXPECT_EQ(ont_parser_init_test_uint32(&elem), ONT_ERR_OK);
    elem.elem.value = 32;

    EXPECT_EQ(ont_parser_len(&elem.head, &len), ONT_ERR_OK);
    EXPECT_EQ(len, 4);
    EXPECT_EQ(ont_parser_serialize(buf, 1, &elem.head), ONT_ERR_NOMEM);
    EXPECT_EQ(ont_parser_serialize(buf, 4, &elem.head), ONT_ERR_OK);
    EXPECT_EQ(strncmp(buf, value, 4), 0);

    EXPECT_EQ(ont_parser_init_test_uint32(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 1, &elem2.head, 0), ONT_ERR_DESERIALIZE_INCOMPLETE);

    EXPECT_EQ(ont_parser_init_test_uint32(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 5, &elem2.head, 0), ONT_ERR_DESERIALIZE_DATA_LEFT);

    EXPECT_EQ(ont_parser_init_test_uint32(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 4, &elem2.head, 0), ONT_ERR_OK);
    EXPECT_EQ(elem.elem.value, elem2.elem.value);
}


ont_parser_def_packet_begin(test_double)
ont_parser_add_elem(elem, double)
ont_parser_def_packet_end(test_double)

ont_parser_init_begin(test_double, elem, double)
ont_parser_init_end()

TEST_F(ParserTest, TestDouble){
    test_double elem;
    test_double elem2;
    size_t len = 0;
    char buf[100];
    uint8_t value[] = {0x3f, 0xf3, 0xae, 0x14, 0x7a, 0xe1, 0x47, 0xae};
    memset(buf, 0, 100);

    EXPECT_EQ(ont_parser_init_test_double(&elem), ONT_ERR_OK);
    elem.elem.value = 1.23;

    EXPECT_EQ(ont_parser_len(&elem.head, &len), ONT_ERR_OK);
    EXPECT_EQ(len, 8);
    EXPECT_EQ(ont_parser_serialize(buf, 1, &elem.head), ONT_ERR_NOMEM);
    EXPECT_EQ(ont_parser_serialize(buf, 8, &elem.head), ONT_ERR_OK);
    EXPECT_EQ(strncmp(buf, (char*)value, 8), 0);

    EXPECT_EQ(ont_parser_init_test_double(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 1, &elem2.head, 0), ONT_ERR_DESERIALIZE_INCOMPLETE);

    EXPECT_EQ(ont_parser_init_test_double(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 9, &elem2.head, 0), ONT_ERR_DESERIALIZE_DATA_LEFT);

    EXPECT_EQ(ont_parser_init_test_double(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 8, &elem2.head, 0), ONT_ERR_OK);
    EXPECT_EQ(elem.elem.value, elem2.elem.value);
}

ont_parser_def_packet_begin(test_string)
ont_parser_add_elem(elem, string)
ont_parser_def_packet_end(test_string)

ont_parser_init_begin(test_string, elem, string)
ont_parser_init_end()

TEST_F(ParserTest, TestString){
    test_string elem;
    test_string elem2;
    size_t len = 0;
    char buf[100];
    memset(buf, 0, 100);

    EXPECT_EQ(ont_parser_init_test_string(&elem), ONT_ERR_OK);
    elem.elem.value = (char*)"abcd";

    EXPECT_EQ(ont_parser_len(&elem.head, &len), ONT_ERR_OK);
    EXPECT_EQ(len, 5);
    EXPECT_EQ(ont_parser_serialize(buf, 1, &elem.head), ONT_ERR_NOMEM);
    EXPECT_EQ(ont_parser_serialize(buf, 5, &elem.head), ONT_ERR_OK);
    EXPECT_EQ(strncmp(buf, "abcd", 5), 0);

    EXPECT_EQ(ont_parser_init_test_string(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 1, &elem2.head, 0), ONT_ERR_DESERIALIZE_INCOMPLETE);

    EXPECT_EQ(ont_parser_init_test_string(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 6, &elem2.head, 0), ONT_ERR_DESERIALIZE_DATA_LEFT);

    EXPECT_EQ(ont_parser_init_test_string(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 5, &elem2.head, 0), ONT_ERR_OK);
    EXPECT_EQ(strcmp(elem.elem.value, elem2.elem.value), 0);
}

ont_parser_def_packet_begin(test_bytes)
ont_parser_add_elem(elem, bytes)
ont_parser_def_packet_end(test_bytes)

ont_parser_init_begin(test_bytes, elem, bytes)
ont_parser_init_end()

TEST_F(ParserTest, TestBytes){
    test_bytes elem;
    test_bytes elem2;
    size_t len = 0;
    char buf[100];
    memset(buf, 0, 100);

    EXPECT_EQ(ont_parser_init_test_bytes(&elem), ONT_ERR_OK);
    elem.elem.len = 4;
    elem.elem.value = (char*)"abcd";

    EXPECT_EQ(ont_parser_len(&elem.head, &len), ONT_ERR_OK);
    EXPECT_EQ(len, 6);
    EXPECT_EQ(ont_parser_serialize(buf, 1, &elem.head), ONT_ERR_NOMEM);
    EXPECT_EQ(ont_parser_serialize(buf, 6, &elem.head), ONT_ERR_OK);
    EXPECT_EQ((uint8_t)buf[0], 0x00);
    EXPECT_EQ((uint8_t)buf[1], 0x04);
    EXPECT_EQ(strncmp(buf+2, "abcd", 4), 0);

    EXPECT_EQ(ont_parser_init_test_bytes(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 1, &elem2.head, 0), ONT_ERR_DESERIALIZE_INCOMPLETE);

    EXPECT_EQ(ont_parser_init_test_bytes(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 7, &elem2.head, 0), ONT_ERR_DESERIALIZE_DATA_LEFT);

    EXPECT_EQ(ont_parser_init_test_bytes(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 6, &elem2.head, 0), ONT_ERR_OK);
    EXPECT_EQ(elem2.elem.len, 4);
    EXPECT_EQ(strncmp(elem.elem.value, elem2.elem.value, 4), 0);
}

ont_parser_def_packet_begin(test_binary)
ont_parser_add_elem(elem, binary)
ont_parser_def_packet_end(test_binary)

ont_parser_init_begin(test_binary, elem, binary)
ont_parser_init_end()

TEST_F(ParserTest, TestBinary){
    test_binary elem;
    test_binary elem2;
    size_t len = 0;
    char buf[100];
    memset(buf, 0, 100);

    EXPECT_EQ(ont_parser_init_test_binary(&elem), ONT_ERR_OK);
    elem.elem.len = 4;
    elem.elem.value = (char*)"abcd";

    EXPECT_EQ(ont_parser_len(&elem.head, &len), ONT_ERR_OK);
    EXPECT_EQ(len, 8);
    EXPECT_EQ(ont_parser_serialize(buf, 1, &elem.head), ONT_ERR_NOMEM);
    EXPECT_EQ(ont_parser_serialize(buf, 8, &elem.head), ONT_ERR_OK);
    EXPECT_EQ((uint8_t)buf[0], 0x00);
    EXPECT_EQ((uint8_t)buf[1], 0x00);
    EXPECT_EQ((uint8_t)buf[2], 0x00);
    EXPECT_EQ((uint8_t)buf[3], 0x04);
    EXPECT_EQ(strncmp(buf+4, "abcd", 4), 0);

    EXPECT_EQ(ont_parser_init_test_binary(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 1, &elem2.head, 0), ONT_ERR_DESERIALIZE_INCOMPLETE);

    EXPECT_EQ(ont_parser_init_test_binary(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 9, &elem2.head, 0), ONT_ERR_DESERIALIZE_DATA_LEFT);

    EXPECT_EQ(ont_parser_init_test_binary(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 8, &elem2.head, 0), ONT_ERR_OK);
    EXPECT_EQ(elem2.elem.len, 4);
    EXPECT_EQ(strncmp(elem.elem.value, elem2.elem.value, 4), 0);
}

ont_parser_def_packet_begin(test_raw)
ont_parser_add_elem(elem, raw)
ont_parser_def_packet_end(test_raw)

ont_parser_init_begin(test_raw, elem, raw)
ont_parser_init_end()

TEST_F(ParserTest, TestRaw){
    test_raw elem;
    test_raw elem2;
    size_t len = 0;
    char buf[100];
    memset(buf, 0, 100);

    EXPECT_EQ(ont_parser_init_test_raw(&elem), ONT_ERR_OK);
    elem.elem.len = 4;
    elem.elem.value = (char*)"abcd";

    EXPECT_EQ(ont_parser_len(&elem.head, &len), ONT_ERR_OK);
    EXPECT_EQ(len, 4);
    EXPECT_EQ(ont_parser_serialize(buf, 1, &elem.head), ONT_ERR_NOMEM);
    EXPECT_EQ(ont_parser_serialize(buf, 4, &elem.head), ONT_ERR_OK);
    EXPECT_EQ(strncmp(buf, "abcd", 4), 0);

    EXPECT_EQ(ont_parser_init_test_raw(&elem2), ONT_ERR_OK);
    elem2.elem.len = 4;
    EXPECT_EQ(ont_parser_deserialize(buf, 1, &elem2.head, 0), ONT_ERR_DESERIALIZE_INCOMPLETE);

    EXPECT_EQ(ont_parser_init_test_raw(&elem2), ONT_ERR_OK);
    elem2.elem.len = 4;
    EXPECT_EQ(ont_parser_deserialize(buf, 5, &elem2.head, 0), ONT_ERR_DESERIALIZE_DATA_LEFT);

    EXPECT_EQ(ont_parser_init_test_raw(&elem2), ONT_ERR_OK);
    elem2.elem.len = 4;
    EXPECT_EQ(ont_parser_deserialize(buf, 4, &elem2.head, 0), ONT_ERR_OK);
    EXPECT_EQ(strncmp(elem.elem.value, elem2.elem.value, 4), 0);
}

ont_parser_def_packet_begin(test_compress_uint32)
ont_parser_add_elem(elem, compress_uint32)
ont_parser_def_packet_end(test_compress_uint32)

ont_parser_init_begin(test_compress_uint32, elem, compress_uint32)
ont_parser_init_end()

TEST_F(ParserTest, TestCompress_Uint32_1bit){
    test_compress_uint32 elem;
    test_compress_uint32 elem2;
    size_t len = 0;
    char buf[100];
    memset(buf, 0, 100);

    EXPECT_EQ(ont_parser_init_test_compress_uint32(&elem), ONT_ERR_OK);
    elem.elem.value = 1;

    EXPECT_EQ(ont_parser_len(&elem.head, &len), ONT_ERR_OK);
    EXPECT_EQ(len, 1);
    EXPECT_EQ(ont_parser_serialize(buf, 0, &elem.head), ONT_ERR_NOMEM);
    EXPECT_EQ(ont_parser_serialize(buf, 1, &elem.head), ONT_ERR_OK);
    EXPECT_EQ((uint8_t)buf[0], 0x01);

    EXPECT_EQ(ont_parser_init_test_compress_uint32(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 0, &elem2.head, 0), ONT_ERR_DESERIALIZE_INCOMPLETE);

    EXPECT_EQ(ont_parser_init_test_compress_uint32(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 2, &elem2.head, 0), ONT_ERR_DESERIALIZE_DATA_LEFT);

    EXPECT_EQ(ont_parser_init_test_compress_uint32(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 1, &elem2.head, 0), ONT_ERR_OK);
    EXPECT_EQ(elem2.elem.value, 1);
}

TEST_F(ParserTest, TestCompress_Uint32_2bit){
    test_compress_uint32 elem;
    test_compress_uint32 elem2;
    size_t len = 0;
    char buf[100];
    memset(buf, 0, 100);

    EXPECT_EQ(ont_parser_init_test_compress_uint32(&elem), ONT_ERR_OK);
    elem.elem.value = 128;

    EXPECT_EQ(ont_parser_len(&elem.head, &len), ONT_ERR_OK);
    EXPECT_EQ(len, 2);
    EXPECT_EQ(ont_parser_serialize(buf, 1, &elem.head), ONT_ERR_NOMEM);
    EXPECT_EQ(ont_parser_serialize(buf, 2, &elem.head), ONT_ERR_OK);
    EXPECT_EQ((uint8_t)buf[0], 0x80);
    EXPECT_EQ((uint8_t)buf[1], 0x01);

    EXPECT_EQ(ont_parser_init_test_compress_uint32(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 1, &elem2.head, 0), ONT_ERR_DESERIALIZE_INCOMPLETE);

    EXPECT_EQ(ont_parser_init_test_compress_uint32(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 3, &elem2.head, 0), ONT_ERR_DESERIALIZE_DATA_LEFT);

    EXPECT_EQ(ont_parser_init_test_compress_uint32(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 2, &elem2.head, 0), ONT_ERR_OK);
    EXPECT_EQ(elem2.elem.value, 128);
}

TEST_F(ParserTest, TestCompress_Uint32_3bit){
    test_compress_uint32 elem;
    test_compress_uint32 elem2;
    size_t len = 0;
    char buf[100];
    memset(buf, 0, 100);

    EXPECT_EQ(ont_parser_init_test_compress_uint32(&elem), ONT_ERR_OK);
    elem.elem.value = 16384;

    EXPECT_EQ(ont_parser_len(&elem.head, &len), ONT_ERR_OK);
    EXPECT_EQ(len, 3);
    EXPECT_EQ(ont_parser_serialize(buf, 1, &elem.head), ONT_ERR_NOMEM);
    EXPECT_EQ(ont_parser_serialize(buf, 3, &elem.head), ONT_ERR_OK);
    EXPECT_EQ((uint8_t)buf[0], 0x80);
    EXPECT_EQ((uint8_t)buf[1], 0x80);
    EXPECT_EQ((uint8_t)buf[2], 0x01);

    EXPECT_EQ(ont_parser_init_test_compress_uint32(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 2, &elem2.head, 0), ONT_ERR_DESERIALIZE_INCOMPLETE);

    EXPECT_EQ(ont_parser_init_test_compress_uint32(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 4, &elem2.head, 0), ONT_ERR_DESERIALIZE_DATA_LEFT);

    EXPECT_EQ(ont_parser_init_test_compress_uint32(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 3, &elem2.head, 0), ONT_ERR_OK);
    EXPECT_EQ(elem2.elem.value, 16384);
}

TEST_F(ParserTest, TestCompress_Uint32_4bit){
    test_compress_uint32 elem;
    test_compress_uint32 elem2;
    size_t len = 0;
    char buf[100];
    memset(buf, 0, 100);

    EXPECT_EQ(ont_parser_init_test_compress_uint32(&elem), ONT_ERR_OK);
    elem.elem.value = 2097152;

    EXPECT_EQ(ont_parser_len(&elem.head, &len), ONT_ERR_OK);
    EXPECT_EQ(len, 4);
    EXPECT_EQ(ont_parser_serialize(buf, 3, &elem.head), ONT_ERR_NOMEM);
    EXPECT_EQ(ont_parser_serialize(buf, 4, &elem.head), ONT_ERR_OK);
    EXPECT_EQ((uint8_t)buf[0], 0x80);
    EXPECT_EQ((uint8_t)buf[1], 0x80);
    EXPECT_EQ((uint8_t)buf[2], 0x80);
    EXPECT_EQ((uint8_t)buf[3], 0x01);

    EXPECT_EQ(ont_parser_init_test_compress_uint32(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 3, &elem2.head, 0), ONT_ERR_DESERIALIZE_INCOMPLETE);

    EXPECT_EQ(ont_parser_init_test_compress_uint32(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 5, &elem2.head, 0), ONT_ERR_DESERIALIZE_DATA_LEFT);

    EXPECT_EQ(ont_parser_init_test_compress_uint32(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 4, &elem2.head, 0), ONT_ERR_OK);
    EXPECT_EQ(elem2.elem.value, 2097152);
}

TEST_F(ParserTest, TestCompress_Uint32_overload){
    test_compress_uint32 elem;
    test_compress_uint32 elem2;
    size_t len = 0;
    char buf[100];
    memset(buf, 0, 100);

    EXPECT_EQ(ont_parser_init_test_compress_uint32(&elem), ONT_ERR_OK);
    elem.elem.value = 268435456;

    EXPECT_EQ(ont_parser_len(&elem.head, &len), ONT_ERR_REMAIN_LEN_OVER_RANGE);
    EXPECT_EQ(ont_parser_serialize(buf, 1, &elem.head), ONT_ERR_NOMEM);
    EXPECT_EQ(ont_parser_serialize(buf, 4, &elem.head), ONT_ERR_REMAIN_LEN_OVER_RANGE);


    buf[0] = (uint8_t)0x80;
    buf[1] = (uint8_t)0x80;
    buf[2] = (uint8_t)0x80;
    buf[3] = (uint8_t)0x80;
    EXPECT_EQ(ont_parser_init_test_compress_uint32(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 4, &elem2.head, 0), ONT_ERR_REMAIN_LEN_OVER_RANGE);
}

ont_parser_def_packet_begin(test_ref)
ont_parser_add_elem(elem, uint16)
ont_parser_add_ref_elem(qos)
ont_parser_add_ref_elem(retain)
ont_parser_def_packet_end(test_ref)

ont_parser_init_begin(test_ref, elem, uint16)
ont_parser_queue_up_ref_elem(qos, elem, 8, 9)
ont_parser_queue_up_ref_elem(retain, elem, 0, 1)
ont_parser_init_end()

TEST_F(ParserTest, TestRef){
    test_ref elem;
    test_ref elem2;
    size_t len = 0;
    char buf[100];
    memset(buf, 0, 100);

    EXPECT_EQ(ont_parser_init_test_ref(&elem), ONT_ERR_OK);
    elem.qos.value = 3;
    elem.retain.value = 1;

    EXPECT_EQ(ont_parser_len(&elem.head, &len), ONT_ERR_OK);
    EXPECT_EQ(len, 2);
    EXPECT_EQ(ont_parser_serialize(buf, 1, &elem.head), ONT_ERR_NOMEM);
    EXPECT_EQ(ont_parser_serialize(buf, 2, &elem.head), ONT_ERR_OK);
    EXPECT_EQ((uint8_t)buf[0], 0x03);
    EXPECT_EQ((uint8_t)buf[1], 0x01);

    EXPECT_EQ(ont_parser_init_test_ref(&elem2), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_deserialize(buf, 1, &elem2.head, 0), ONT_ERR_DESERIALIZE_INCOMPLETE);
    EXPECT_EQ(ont_parser_deserialize(buf, 2, &elem2.head, 0), ONT_ERR_OK);
    EXPECT_EQ(elem2.qos.value, 3);
    EXPECT_EQ(elem2.retain.value, 1);
}

ont_parser_def_packet_begin(test_ref_over_range)
ont_parser_add_elem(elem, uint16)
ont_parser_add_ref_elem(qos)
ont_parser_def_packet_end(test_ref_over_range)

ont_parser_init_begin(test_ref_over_range, elem, uint16)
ont_parser_queue_up_ref_elem(qos, elem, 0, 8)
ont_parser_init_end()

TEST_F(ParserTest, TestRefOverRange){
    test_ref_over_range elem;
    EXPECT_EQ(ont_parser_init_test_ref_over_range(&elem), ONT_ERR_REFERENCE_OVER_RANGE);
}

ont_parser_def_packet_begin(test_ref_double)
ont_parser_add_elem(elem, double)
ont_parser_add_ref_elem(qos)
ont_parser_def_packet_end(test_ref_double)

ont_parser_init_begin(test_ref_double, elem, string)
ont_parser_queue_up_ref_elem(qos, elem, 0, 1)
ont_parser_init_end()

TEST_F(ParserTest, TestRefWrongTypeDouble){
    test_ref_double elem;
    EXPECT_EQ(ont_parser_init_test_ref_double(&elem), ONT_ERR_REFERENCE_WRONG_TYPE);
}

ont_parser_def_packet_begin(test_ref_string)
ont_parser_add_elem(elem, string)
ont_parser_add_ref_elem(qos)
ont_parser_def_packet_end(test_ref_string)

ont_parser_init_begin(test_ref_string, elem, string)
ont_parser_queue_up_ref_elem(qos, elem, 0, 1)
ont_parser_init_end()

TEST_F(ParserTest, TestRefWrongTypeString){
    test_ref_string elem;
    EXPECT_EQ(ont_parser_init_test_ref_string(&elem), ONT_ERR_REFERENCE_WRONG_TYPE);
}

ont_parser_def_packet_begin(test_ref_bytes)
ont_parser_add_elem(elem, bytes)
ont_parser_add_ref_elem(qos)
ont_parser_def_packet_end(test_ref_bytes)

ont_parser_init_begin(test_ref_bytes, elem, bytes)
ont_parser_queue_up_ref_elem(qos, elem, 0, 1)
ont_parser_init_end()

TEST_F(ParserTest, TestRefWrongTypeBytes){
    test_ref_bytes elem;
    EXPECT_EQ(ont_parser_init_test_ref_bytes(&elem), ONT_ERR_REFERENCE_WRONG_TYPE);
}

ont_parser_def_packet_begin(test_ref_binary)
ont_parser_add_elem(elem, binary)
ont_parser_add_ref_elem(qos)
ont_parser_def_packet_end(test_ref_binary)

ont_parser_init_begin(test_ref_binary, elem, binary)
ont_parser_queue_up_ref_elem(qos, elem, 0, 1)
ont_parser_init_end()

TEST_F(ParserTest, TestRefWrongTypeBinary){
    test_ref_binary elem;
    EXPECT_EQ(ont_parser_init_test_ref_binary(&elem), ONT_ERR_REFERENCE_WRONG_TYPE);
}

ont_parser_def_packet_begin(test_ref_raw)
ont_parser_add_elem(elem, raw)
ont_parser_add_ref_elem(qos)
ont_parser_def_packet_end(test_ref_raw)

ont_parser_init_begin(test_ref_raw, elem, raw)
ont_parser_queue_up_ref_elem(qos, elem, 0, 1)
ont_parser_init_end()

TEST_F(ParserTest, TestRefWrongTypeRaw){
    test_ref_raw elem;
    EXPECT_EQ(ont_parser_init_test_ref_raw(&elem), ONT_ERR_REFERENCE_WRONG_TYPE);
}

ont_parser_def_packet_begin(test_ref_compress_uint32)
ont_parser_add_elem(elem, compress_uint32)
ont_parser_add_ref_elem(qos)
ont_parser_def_packet_end(test_ref_compress_uint32)

ont_parser_init_begin(test_ref_compress_uint32, elem, compress_uint32)
ont_parser_queue_up_ref_elem(qos, elem, 0, 1)
ont_parser_init_end()

TEST_F(ParserTest, TestRefWrongTypeCompressUint32){
    test_ref_compress_uint32 elem;
    EXPECT_EQ(ont_parser_init_test_ref_compress_uint32(&elem), ONT_ERR_REFERENCE_WRONG_TYPE);
}

int32_t int8_filter(ont_parser_list_node_t* node){
    ont_parser_uint8_t* p = (ont_parser_uint8_t*)node;
    if (p->value != 0){
        return 0;
    }

    return 1;
}

ont_parser_def_packet_begin(test_pkt)
ont_parser_add_elem(test_uint8, uint8)
ont_parser_add_elem(test_uint16, uint16)
ont_parser_add_elem(test_uint32, uint32)
ont_parser_add_elem(test_double, double)
ont_parser_add_elem(test_string, string)
ont_parser_add_elem(test_bytes, bytes)
ont_parser_add_elem(test_binary, binary)
ont_parser_add_elem(test_raw, raw)
ont_parser_add_elem(test_compress_uint32, compress_uint32)
ont_parser_add_ref_elem(qos)
ont_parser_add_ref_elem(retain)
ont_parser_def_packet_end(test_pkt)

ont_parser_init_begin(test_pkt, test_uint8, uint8)
ont_parser_queue_up(test_uint16, uint16, int8_filter, test_uint8);
ont_parser_queue_up(test_uint32, uint32, int8_filter, test_uint8);
ont_parser_queue_up(test_double, double, int8_filter, test_uint8);
ont_parser_queue_up(test_string, string, int8_filter, test_uint8);
ont_parser_queue_up(test_bytes, bytes, int8_filter, test_uint8);
ont_parser_queue_up(test_binary, binary, int8_filter, test_uint8);
ont_parser_queue_up(test_raw, raw, int8_filter, test_uint8);
ont_parser_queue_up(test_compress_uint32, compress_uint32, int8_filter, test_uint8);
ont_parser_queue_up_ref_elem(qos, test_uint16, 4, 5)
ont_parser_queue_up_ref_elem(retain, test_uint16, 0, 3)
ont_parser_init_end()

TEST_F(ParserTest, TestFilter){
    test_pkt elem;
    char buf[100];
    size_t len = 0;

    memset(buf, 0, 100);

    EXPECT_EQ(ont_parser_init_test_pkt(&elem), ONT_ERR_OK);
    EXPECT_EQ(ont_parser_len(&elem.head, &len), ONT_ERR_OK);
    EXPECT_EQ(len, 1);
    EXPECT_EQ(ont_parser_serialize(buf, 0, &elem.head), ONT_ERR_NOMEM);
    EXPECT_EQ(ont_parser_serialize(buf, 1, &elem.head), ONT_ERR_OK);

    elem.test_uint8.value = 1;
    EXPECT_EQ(ont_parser_len(&elem.head, &len), ONT_ERR_OK);
    EXPECT_EQ(len, 23);
    EXPECT_EQ(ont_parser_serialize(buf, 20, &elem.head), ONT_ERR_NOMEM);
    EXPECT_EQ(ont_parser_serialize(buf, 23, &elem.head), ONT_ERR_OK);
    EXPECT_EQ((uint8_t)buf[0], 1);
    for (int i=1; i<23; ++i){
        EXPECT_EQ((uint8_t)buf[i], 0);
    }
}

TEST_F(ParserTest, TestAll){
    test_pkt elem;
    char buf[100];
    size_t len = 0;
    uint8_t s_buf[] = {0x08, 0x0, 0x10, 0x0, 0x0, 0x0, 0x20, 0x3F, 0xF3, 0xBE, 0x76, 0xC8, 0xB4, 0x39, 0x58, 0x61, 0x62, 0x63, 0x64, 0x0, 0x0, 0x2, 0x61, 0x62, 0x0, 0x0, 0x0, 0x4, 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64, 0x82, 0x01};

    memset(buf, 0, 100);
    EXPECT_EQ(ont_parser_init_test_pkt(&elem), ONT_ERR_OK);

    elem.test_uint8.value = 8;
    elem.test_uint16.value = 0;
    elem.qos.value = 1;          /* ref : test_int16[4-5] */
    elem.retain.value = 0;       /* ref : test_int16[0-3] */
    elem.test_uint32.value = 32;
    elem.test_double.value = 1.234;
    elem.test_string.value = (char*)"abcd";
    elem.test_bytes.len = 2;
    elem.test_bytes.value = "ab";
    elem.test_binary.len = 4;
    elem.test_binary.value = "abcd";
    elem.test_raw.len = 4;
    elem.test_raw.value = "abcd";
    elem.test_compress_uint32.value = 130;

    EXPECT_EQ(ont_parser_len(&elem.head, &len), ONT_ERR_OK);
    EXPECT_EQ(len, 38);
    EXPECT_EQ(ont_parser_serialize(buf, 0, &elem.head), ONT_ERR_NOMEM);
    EXPECT_EQ(ont_parser_serialize(buf, 38, &elem.head), ONT_ERR_OK);
    EXPECT_EQ(memcmp(buf, s_buf, len), 0);

}
