#include "ont/device.h"
#include "ont/log.h"
#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "ont_mqtt.h"
#include "mqtt.h"
#include "ont_mqtt_private.h"
#include <gtest/gtest.h>
#include "dynamic-stub-manager.h"
#define CHECK_RET(ret)\
    do\
    {\
        if (ret)\
        {\
            printf("[ line %d ] Error:%d\n", __LINE__, ret);\
            return ret;\
        }\
        printf("[ line %d ] Run Ok!\n", __LINE__);\
    } while (0)
static ont_device_t *dev = NULL;
class MqttTest:public testing::Test
{
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
public:
	ont_mqtt_device_t* mqtt_instance;
	
};
int MqttDeviceCreate(ont_device_t *dev)
{
	//ont_mqtt_create(&dev);
	
	memset(dev, 0, sizeof(ont_device_t));
	
    dev->type = ONTDEV_MQTT;
    dev->device_id = 212269;
    dev->product_id = 339;
	dev->key = "Qtis5YAThi3sZVPqzY28c=mW5BI=";
	dev->keepalive = 120;
	dev->exit = 0;
	
	strncpy(dev->ip,"172.19.3.1",strlen("172.19.3.1"));
	dev->port = 10019;
	
	const char *auth_info = "MQTT_DEVICE:212269";
	
	size_t name_len = 0;
    name_len = strlen("MQTT_TEST_DEVICE");

    memcpy(dev->name, "MQTT_TEST_DEVICE", name_len);
    dev->name[name_len] = '\0';

    dev->formatter =
        (ont_pkt_formatter_t*)ont_platform_malloc(sizeof(ont_pkt_formatter_t));
	
	ont_pkt_formatter_init(dev->formatter);
}
void *mqtt_device_malloc_hook(size_t size)
{
	(void ) (size);
	return NULL;
}
TEST_F(MqttTest,MqttInstanceCreate)
{
	DynamicStubManager mgr;
    mgr.MakeStub(ont_platform_malloc, mqtt_device_malloc_hook);
	
	EXPECT_EQ(ONT_ERR_NOMEM,ont_mqtt_create(&dev));
	
	mgr.UnmakeStub(ont_platform_malloc);
	
	ont_mqtt_create(&dev);
	EXPECT_NE(true,dev == NULL);
	MqttDeviceCreate(dev);
	//ont_mqtt_destroy(dev);
}
TEST_F(MqttTest,MqttConnect)
{
	
	//MqttDeviceCreate(dev);
	//printf("dev = %d\n",dev);
	
	EXPECT_EQ(ONT_ERR_BADPARAM,ont_mqtt_connect(NULL,"MQTT_DEVICE:212269"));
		
	dev->key = "Qtis5YAThi3sZVPqzY28c=mW5455";
	
	EXPECT_EQ(ONT_ERR_FAILED_TO_AUTH,ont_mqtt_connect(dev,"MQTT_DEVICE:212269"));
	
	dev->key = "Qtis5YAThi3sZVPqzY28c=mW5BI=";
	EXPECT_EQ(ONT_ERR_OK,ont_mqtt_connect(dev,"MQTT_DEVICE:212269"));
	
	//ont_mqtt_destroy(dev);
}

TEST_F(MqttTest,MqttSubScribeTest)
{

	//MqttDeviceCreate(dev);
	
	//ont_mqtt_connect(dev,"mqtt_test_device");
	
	const char *subscribe_topic_array[]={"topic_test","hello_iot"};
	
	EXPECT_EQ(ONT_ERR_BADPARAM,ont_mqtt_sub_topic(NULL,(const char **)&subscribe_topic_array,2));
	
	EXPECT_EQ(ONT_ERR_BADPARAM,ont_mqtt_sub_topic(dev,NULL,2));
	
	EXPECT_EQ(ONT_ERR_BADPARAM,ont_mqtt_sub_topic(dev,(const char **)&subscribe_topic_array,0));
	
	EXPECT_EQ(ONT_ERR_OK,ont_mqtt_sub_topic(dev,(const char **)&subscribe_topic_array,2));
	
	const char *subscribe_topic_array2[]={"chinamobile","topic_iot"};
	
	EXPECT_EQ(NOT_ALL_TOPIC_SUB_SUCC,ont_mqtt_sub_topic(dev,(const char **)&subscribe_topic_array2,2));

	//ont_mqtt_destroy(dev);
}
TEST_F(MqttTest,MqttPublishTest)
{

	//MqttDeviceCreate(dev);
	
	//ont_mqtt_connect(dev,"mqtt_test_device");
	
	const char *publish_topic_name = "hello_iot";
	
	const char *publish_content = "this is a test publish msg";
	
	uint8_t qos_level = 1;
	
	size_t publish_content_size = strlen(publish_content);
	
	EXPECT_EQ(ONT_ERR_BADPARAM,ont_mqtt_publish(NULL,publish_topic_name,publish_content,publish_content_size,1));
	
	EXPECT_EQ(ONT_ERR_BADPARAM,ont_mqtt_publish(dev,NULL,publish_content,publish_content_size,1));
	
	EXPECT_EQ(ONT_ERR_BADPARAM,ont_mqtt_publish(dev,publish_topic_name,NULL,0,1));
	
	EXPECT_EQ(ONT_ERR_BADPARAM,ont_mqtt_publish(dev,publish_topic_name,publish_content,publish_content_size,4));
	
	EXPECT_EQ(ONT_ERR_OK,ont_mqtt_publish(dev,publish_topic_name,publish_content,publish_content_size,1));

	//ont_mqtt_destroy(dev);
}
TEST_F(MqttTest,MqttUnSubScribeTest)
{
	//MqttDeviceCreate(dev);
	
	//ont_mqtt_connect(dev,"mqtt_test_device");
	
	const char *Unsubscribe_topic_array[]={"topic_test","hello_iot"};
	
	EXPECT_EQ(ONT_ERR_BADPARAM,ont_mqtt_unsub_topic(NULL,(const char **)&Unsubscribe_topic_array,2));
	
	EXPECT_EQ(ONT_ERR_BADPARAM,ont_mqtt_unsub_topic(dev,NULL,2));
	
	EXPECT_EQ(ONT_ERR_BADPARAM,ont_mqtt_unsub_topic(dev,(const char **)&Unsubscribe_topic_array,0));
	
	EXPECT_EQ(ONT_ERR_OK,ont_mqtt_unsub_topic(dev,(const char **)&Unsubscribe_topic_array,2));

	ont_mqtt_destroy(dev);
}