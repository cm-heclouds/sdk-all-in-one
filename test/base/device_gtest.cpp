#define GTEST_USE_OWN_TR1_TUPLE 0
#include <gtest/gtest.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "ont_tcp_channel.h"
#include "ont/error.h"
#include "ont/device.h"
#include "dynamic-stub-manager.h"
#include "ont_list.h"
#include "parser/ont_pkt_formatter.h"
using namespace std;



struct ont_ds_t
{
    char type;//fixed value is 8
    char flag;//
    uint32_t ts; //timestamp.
    ont_list_t *dplist;
};
int ont_create( ont_device_t **dev )
{

	
	if(NULL == dev)
	{
		return ONT_ERR_BADPARAM;
	}
	ont_device_t *_instance = (ont_device_t *)malloc(sizeof(ont_device_t));
	if(NULL == _instance)
	{
		return ONT_ERR_NOMEM;
	}
	
	*dev = _instance;

	return ONT_ERR_OK;	
}

/**
 *  * 销毁ONENET接入设备实例
 *   * @param dev OneNET接入设备实例
 *   **/
void ont_destroy( ont_device_t *dev )
{
}

/**
 *  * 与OneNET建立连接
 *   * @param dev OneNET接入设备实例
 *    * @return 连接成功返回ONT_ERR_OK
 *    **/
int ont_connect( ont_device_t *dev, const char *auth_info )
{
	return ONT_ERR_OK;
}

/**
 *  * 发送数据点到OneNET
 *   * @param dev     OneNET接入设备实例
 *    * @param payload 按格式8序列化数据点
 *     * @param bytes   数据点字节数
 *      * @return 成功则返回ONT_ERR_OK
 *      **/
int ont_send_datapoints( ont_device_t *dev,
                                const char *payload,
                                size_t bytes )
{


        char * cmp = (char *)malloc(sizeof(char)*53);
        int j = 0;
        j = sprintf(cmp,"%c",0x08);
	j+= sprintf(cmp+j,"%c",0x00);
        j+= sprintf(cmp+j,"%c",0x05);
        j+= sprintf(cmp+j,"%c",0x01);
        j+= sprintf(cmp+j,"%c",0x31);
        j+= sprintf(cmp+j,"%c",0x00);
        j+= sprintf(cmp+j,"%c",0x00);
        j+= sprintf(cmp+j,"%c",0x00);
        j+= sprintf(cmp+j,"%c",0x00);
        j+= sprintf(cmp+j,"%c",0x6e);
        j+= sprintf(cmp+j,"%c",0x03);
        j+= sprintf(cmp+j,"%c",0x32);
        j+= sprintf(cmp+j,"%c",0x00);
        j+= sprintf(cmp+j,"%c",0x73);
        j+= sprintf(cmp+j,"%c",0x74);
        j+= sprintf(cmp+j,"%c",0x72);
        j+= sprintf(cmp+j,"%c",0x69);
        j+= sprintf(cmp+j,"%c",0x6e);
        j+= sprintf(cmp+j,"%c",0x67);
        j+= sprintf(cmp+j,"%c",0x00);
        j+= sprintf(cmp+j,"%c",0x04);
        j+= sprintf(cmp+j,"%c",0x33);
        j+= sprintf(cmp+j,"%c",0x00);
        j+= sprintf(cmp+j,"%c",0x00);
        j+= sprintf(cmp+j,"%c",0x00);
        j+= sprintf(cmp+j,"%c",0x00);
        j+= sprintf(cmp+j,"%c",0x06);
        j+= sprintf(cmp+j,"%c",0x62);
        j+= sprintf(cmp+j,"%c",0x69);
        j+= sprintf(cmp+j,"%c",0x6e);
        j+= sprintf(cmp+j,"%c",0x61);
        j+= sprintf(cmp+j,"%c",0x72);
        j+= sprintf(cmp+j,"%c",0x79);
        j+= sprintf(cmp+j,"%c",0x02);
        j+= sprintf(cmp+j,"%c",0x34);
        j+= sprintf(cmp+j,"%c",0x00);
        j+= sprintf(cmp+j,"%c",0x3f);
        j+= sprintf(cmp+j,"%c",0xfffffff1);
        j+= sprintf(cmp+j,"%c",0xffffff99);
        j+= sprintf(cmp+j,"%c",0xffffff99);
        j+= sprintf(cmp+j,"%c",0xffffff99);
        j+= sprintf(cmp+j,"%c",0xffffff99);
        j+= sprintf(cmp+j,"%c",0xffffff99);
        j+= sprintf(cmp+j,"%c",0xffffff9a);
        j+= sprintf(cmp+j,"%c",0x05);
        j+= sprintf(cmp+j,"%c",0x35);
        j+= sprintf(cmp+j,"%c",0x00);
        j+= sprintf(cmp+j,"%c",0x7b);
        j+= sprintf(cmp+j,"%c",0x61);
        j+= sprintf(cmp+j,"%c",0x3a);
        j+= sprintf(cmp+j,"%c",0x62);
        j+= sprintf(cmp+j,"%c",0x7d);
        j+= sprintf(cmp+j,"%c",0x00);
	for(size_t i=0;i<bytes;i++)
	{
	//	printf("%d :cmp = %x , payload = %x \n",i+1,cmp[i],payload[i]);
		if(cmp[i]!=payload[i])
			return ONT_ERR_BADPARAM;
	}

	return ONT_ERR_OK;
}

/**
 *  * 获取OneNET平台下发命令
 *   * @param dev OneNET接入设备实例
 *    * @return 获取成功返回有效ont_device_cmd_t指针
 *    **/
ont_device_cmd_t* ont_get_cmd( ont_device_t *dev )
{
	ont_device_cmd_t* ptr = (ont_device_cmd_t *)malloc(sizeof(ont_device_cmd_t));
	ptr->req = (char*)malloc(sizeof(char));
	return ptr;
}

/**
 *  * 发送命令响应数据到OneNET
 *   * @param dev   OneNET接入设备实例
 *    * @param cmdid OneNET平台下发命令的唯一标识
 *     * @param resp  设备响应数据
 *      * @param size  响应数据大小
 *       * @return 发送成功返回ONT_ERR_OK
 *       **/
int ont_reply_cmd( ont_device_t *dev,
                          const char *cmdid,
                          const char *resp,
                          size_t size )
{
	return ONT_ERR_OK;
}

/**
 *  * 检查设备连接、发送心跳、接收OneNET平台下发数据
 *   * @param dev   OneNET接入设备实例
 *   **/
int ont_keepalive( ont_device_t *dev )
{
	return ONT_ERR_OK;
}

class DeviceTest : public testing::Test{
public:
    ont_device_type_t edp_type;
    ont_device_type_t jtext_type;
    ont_device_type_t modbus_type;
    ont_device_type_t mqtt_type;
    virtual void SetUp() {
    edp_type = ONTDEV_EDP;
    jtext_type = ONTDEV_JTEXT;
    modbus_type = ONTDEV_MODBUS;
    mqtt_type = ONTDEV_MQTT;
    }
};
void *malloc_hook(size_t size){
	(void) (size);
	return NULL;
}
const ont_device_rt_t *ont_device_get_rt_hook(ont_device_type_t type)
{
	static ont_device_rt_t _rt = {
            ont_create,
            ont_destroy,
            ont_connect,
            ont_send_datapoints,
            ont_get_cmd,
            ont_reply_cmd,
            ont_keepalive
        };
	switch (type)
	{
	case ONTDEV_EDP:
		break;

	case ONTDEV_JTEXT:
		break;

	case ONTDEV_MQTT:
		break;

	case ONTDEV_MODBUS:
		break;
	default:
		return NULL;
	}
	return &_rt;   
}

static const char *devicefilename ="ont_device_ctx";
static int ont_device_save_status_bad(ont_device_t *dev)
{
    int err = ONT_ERR_OK;

#ifdef ONT_PLATFORM_PERSISTENCE_SUPPORT
    /*
 *      * file format:
 *           *   | total len(2 bytes) |
 *                *   | version(1 bytes)   |
 *                     *   | device id(4 bytes) |
 *                          *   | key len(2 bytes)   |
 *                               *   | key                |
 *                                    */
    uint16_t total_len, key_len;
    char *status, *cursor;
    const uint16_t fix_size = 2 + 1 + 4 + 2;

    key_len = (uint16_t)strlen(dev->key);
    total_len = key_len + fix_size+1;
    status = (char*)ont_platform_malloc(total_len);
    if (!status)
        return ONT_ERR_NOMEM;

    cursor = status;

    memcpy(cursor, &total_len, 2);
    cursor += 2;

    *(cursor++) = 10;

    memcpy(cursor, &dev->device_id, 4);
    cursor += 4;

    memcpy(cursor, &key_len, 2);
    cursor += 2;

    memcpy(cursor, dev->key, key_len);
    err = ont_platform_save_device_status(status, total_len);
    ont_platform_free(status);
#endif /* ONT_PLATFORM_PERSISTENCE_SUPPORT */
    return err;
}

static int ont_device_save_status_(ont_device_t *dev)
{
	int err = ONT_ERR_OK;

#ifdef ONT_PLATFORM_PERSISTENCE_SUPPORT
	uint16_t total_len, key_len;
	char *status, *cursor;
	const uint16_t fix_size = 2 + 1 + 4 + 2;

	key_len = (uint16_t)strlen(dev->key);
	total_len = key_len + fix_size;
	status = (char*)malloc(total_len);
	if (!status)
		return ONT_ERR_NOMEM;

	cursor = status;

	memcpy(cursor, &total_len, 2);
	cursor += 2;

	*(cursor++) = 1;

	memcpy(cursor, &dev->device_id, 4);
	cursor += 4;

	memcpy(cursor, &key_len, 2);
	cursor += 2;

	memcpy(cursor, dev->key, key_len);
	err = ont_platform_save_device_status(status, total_len);
	ont_platform_free(status);
#endif /* ONT_PLATFORM_PERSISTENCE_SUPPORT */
	return err;
}
int ont_tcp_channel_deinitilize_hook(void* ch_ctx)
{
	tcp_channel_t* ctx = NULL;
	ctx = (tcp_channel_t*)ch_ctx;
	ont_platform_free(ctx->buffer_in.begin);  
	ctx->buffer_in.begin = NULL;

	ont_platform_free(ctx->buffer_out.begin); 
	ctx->buffer_out.begin = NULL;

	ont_platform_free(ctx); 
	ctx = NULL;

	return ONT_ERR_OK;
}
int ont_tcp_channel_write_hook(void* ch_ctx, const char* buf, const size_t size)
{
	tcp_channel_t * ctx = NULL;
	ctx = (tcp_channel_t*)ch_ctx;
	ont_device_t *dev = (ont_device_t*)ctx->owner_ctx;
	if(ONTDEV_STATUS_REGISTERING == dev->status)
	{
	const char *http_req =
		"POST /register_de?register_code=egSEGxef6s HTTP/1.1\r\n"
		"Host: 127.0.0.1\r\n"
		"Content-Length: 30\r\n"
		"Connection: close\r\n"
		"\r\n"		
		"{"
		"\"sn\":\"123456\","
		"\"title\":\"name\""
		"}";
	if(strcmp(http_req,buf))
	{
		return ONT_ERR_SOCKET_OP_FAIL; 
	}
	}else
	{
        const char *http_req =
                "GET /s?t=1 HTTP/1.1\r\n"
        	"Host: 127.0.0.1\r\n"
	        "Connection: close\r\n"
	        "\r\n";
	if(strcmp(http_req,buf))
        {
                return ONT_ERR_SOCKET_OP_FAIL;
        }
	}
	return ONT_ERR_OK;
}
int ont_tcp_channel_connect_hook(void* channel, volatile int *exit)
{
	tcp_channel_t* ctx = NULL;
	ctx = (tcp_channel_t*)channel;
	ctx->conn_status = ONT_ERR_OK;
	return ONT_ERR_OK; 
}
int ont_tcp_channel_process_hook(void* ch_ctx)
{
	const char * buf_recv =
		"Content-Length: 74\r\n"
		"\r\n"
		"{"
		"\"errno\":0,\r\n"
		"\"error\":\"succ\",\r\n"
		"\"data\":\r\n"
		"{\r\n"
		"\"key\":\"x\",\r\n"
		"\"device_id\":315,\r\n"
		"}"
		"}";	
	const char * buf_recv_retriev =
		"Content-Length: 15\r\n"
		"\r\n"
		"127.0.0.1:10019";
	size_t buf_size = strlen(buf_recv);
	size_t packet_read_size = 0;
	size_t buf_size_retriev = strlen(buf_recv_retriev);
	tcp_channel_t * ctx = NULL;
	ctx = (tcp_channel_t*)ch_ctx;
	if(ONTDEV_STATUS_RETRIEVING_ACCEPTOR ==((ont_device_t*)ctx->owner_ctx)->status)
	{
		int iret_packet_err = ctx->channel->fn_cb_read_packet(ctx->owner_ctx, buf_recv_retriev, buf_size_retriev, &packet_read_size);
	        if (packet_read_size)
	        {
        	        return iret_packet_err;
	        }

		return ONT_ERR_OK;
	}
	int iret_packet_err = ctx->channel->fn_cb_read_packet(ctx->owner_ctx, buf_recv, buf_size, &packet_read_size);
	if (packet_read_size)
	{
		return iret_packet_err;
	}
	return ONT_ERR_OK;
}
TEST_F(DeviceTest,ont_device_create){
    DynamicStubManager mgr;
    mgr.MakeStub(ont_device_get_rt,ont_device_get_rt_hook);

    ont_device_t *dev = (ont_device_t*)malloc(sizeof(ont_device_t));
    EXPECT_EQ(ONT_ERR_BADPARAM,ont_device_create(315,(ont_device_type_t)NULL,"name",&dev));
    EXPECT_EQ(ONT_ERR_BADPARAM,ont_device_create(315,edp_type,"name",NULL));
    mgr.MakeStub(malloc,malloc_hook);
    EXPECT_EQ(ONT_ERR_NOMEM,ont_device_create(315,edp_type,"name",&dev));
    mgr.UnmakeStub(malloc);
    EXPECT_EQ(ONT_ERR_OK,ont_device_create(315,edp_type,"name",&dev));
    EXPECT_EQ(edp_type,dev->type); 
    EXPECT_EQ(0,dev->device_id);
    EXPECT_EQ(315,dev->product_id);
    mgr.UnmakeStub(ont_device_get_rt);
}
TEST_F(DeviceTest,ont_device_connect_badparam){
    ont_device_t *dev = (ont_device_t*)malloc(sizeof(ont_device_t));
    EXPECT_EQ(ONT_ERR_BADPARAM,ont_device_connect(dev,NULL,2,NULL,NULL,300));
    EXPECT_EQ(ONT_ERR_BADPARAM,ont_device_connect(dev,"172.19.3.1",2,NULL,NULL,300));
    EXPECT_EQ(ONT_ERR_BADPARAM,ont_device_connect(dev,NULL,2020,NULL,NULL,300));
    EXPECT_EQ(ONT_ERR_BADPARAM,ont_device_connect(dev,"172.19.3.1",8080,"mxjd",NULL,300));
}
TEST_F(DeviceTest,ont_device_connect_loadfile){
    DynamicStubManager mgr;
    mgr.MakeStub(ont_device_get_rt,ont_device_get_rt_hook);
    mgr.MakeStub(ont_tcp_channel_process,ont_tcp_channel_process_hook);
    mgr.MakeStub(ont_tcp_channel_connect,ont_tcp_channel_connect_hook);
    mgr.MakeStub(ont_tcp_channel_deinitilize,ont_tcp_channel_deinitilize_hook);
    mgr.MakeStub(ont_tcp_channel_write,ont_tcp_channel_write_hook);
    ont_device_t *dev = (ont_device_t*)malloc(sizeof(ont_device_t));
    EXPECT_EQ(ONT_ERR_OK,ont_device_create(315,edp_type,"name",&dev));
    /*make a ont_device_ctx */
    dev->device_id = 0;
    dev->product_id=314;
    dev->key =(char*) "x";
    /*bad file test */
    ont_device_save_status_bad(dev);
    EXPECT_NE(ONT_ERR_OK,ont_device_connect(dev,"127.0.0.1",10019,"egSEGxef6s","123456",300));    
    /*empty file test*/
    remove(devicefilename);
    EXPECT_EQ(ONT_ERR_OK,ont_device_connect(dev,"127.0.0.1",10019,"egSEGxef6s","123456",300)); 
    
    /*correct file test*/
    ont_device_save_status_(dev);
    /*simulate malloc error test */
    mgr.MakeStub(ont_platform_malloc,malloc_hook);
    EXPECT_EQ(ONT_ERR_NOMEM,ont_device_connect(dev,"127.0.0.1",10019,"egSEGxef6s","123456",300));
    mgr.UnmakeStub(ont_platform_malloc);
    mgr.UnmakeStub(ont_device_get_rt);
    mgr.UnmakeStub(ont_tcp_channel_process);
    mgr.UnmakeStub(ont_tcp_channel_connect);
    mgr.UnmakeStub(ont_tcp_channel_write);
    mgr.UnmakeStub(ont_tcp_channel_deinitilize);
}



TEST_F(DeviceTest,ont_device_connect){
    DynamicStubManager mgr;
    mgr.MakeStub(ont_device_get_rt,ont_device_get_rt_hook);
    mgr.MakeStub(ont_tcp_channel_process,ont_tcp_channel_process_hook);
    mgr.MakeStub(ont_tcp_channel_connect,ont_tcp_channel_connect_hook); 
    mgr.MakeStub(ont_tcp_channel_write,ont_tcp_channel_write_hook);
    mgr.MakeStub(ont_tcp_channel_deinitilize,ont_tcp_channel_deinitilize_hook);    
    ont_device_t *dev = (ont_device_t*)malloc(sizeof(ont_device_t));

    EXPECT_EQ(ONT_ERR_OK,ont_device_create(314,edp_type,"name",&dev));
 
    remove(devicefilename);
 //ont_device_register http_req test
    //wrong test
    EXPECT_EQ(ONT_ERR_SOCKET_OP_FAIL,ont_device_connect(dev,"127.0.0.1",10019,"egSEGxef6s","1234567",300));
    remove(devicefilename);
    EXPECT_EQ(ONT_ERR_OK,ont_device_connect(dev,"127.0.0.1",10019,"egSEGxef6s","123456",300));    
    EXPECT_EQ(10019,dev->port);
    EXPECT_EQ(0,strcmp("127.0.0.1",dev->ip));
    EXPECT_EQ(315,dev->device_id);
    EXPECT_EQ(314,dev->product_id);
//    EXPECT_EQ(0,strcmp("x",dev->key)); 
    EXPECT_EQ(300,dev->keepalive);
   // EXPECT_EQ(ONTDEV_STATUS_REGISTERING,(*dev)->status);
    
    mgr.UnmakeStub(ont_tcp_channel_process);
    mgr.UnmakeStub(ont_device_get_rt);
    mgr.UnmakeStub(ont_tcp_channel_connect);
    mgr.UnmakeStub(ont_tcp_channel_write);
    mgr.UnmakeStub(ont_tcp_channel_deinitilize);
}
TEST_F(DeviceTest,ont_device_dp_send)
{
    DynamicStubManager mgr;
    mgr.MakeStub(ont_device_get_rt,ont_device_get_rt_hook);
    mgr.MakeStub(ont_tcp_channel_process,ont_tcp_channel_process_hook);
    mgr.MakeStub(ont_tcp_channel_connect,ont_tcp_channel_connect_hook);
    mgr.MakeStub(ont_tcp_channel_write,ont_tcp_channel_write_hook);
    mgr.MakeStub(ont_tcp_channel_deinitilize,ont_tcp_channel_deinitilize_hook);
    ont_device_t *dev = (ont_device_t*)malloc(sizeof(ont_device_t));
    EXPECT_EQ(ONT_ERR_OK,ont_device_create(314,edp_type,"name",&dev));
    remove(devicefilename);
    EXPECT_EQ(ONT_ERR_OK,ont_device_connect(dev,"127.0.0.1",10019,"egSEGxef6s","123456",300));

    EXPECT_EQ(ONT_ERR_OK,ont_device_add_dp_int(dev,"1",110));
    EXPECT_EQ(ONT_ERR_OK,ont_device_add_dp_string(dev,"2","string"));
    EXPECT_EQ(ONT_ERR_OK,ont_device_add_dp_binary(dev,"3","binary",6));
    EXPECT_EQ(ONT_ERR_OK,ont_device_add_dp_double(dev,"4",1.1));
    EXPECT_EQ(ONT_ERR_OK,ont_device_add_dp_object(dev,"5","{a:b}"));
    EXPECT_EQ(ONT_ERR_OK,ont_device_send_dp(dev));
    mgr.UnmakeStub(ont_tcp_channel_process);
    mgr.UnmakeStub(ont_device_get_rt);
    mgr.UnmakeStub(ont_tcp_channel_connect);
    mgr.UnmakeStub(ont_tcp_channel_write);
    mgr.UnmakeStub(ont_tcp_channel_deinitilize);
}
TEST_F(DeviceTest,ont_device_dp_send_invalid_param)
{
    DynamicStubManager mgr;
    mgr.MakeStub(ont_device_get_rt,ont_device_get_rt_hook);
    mgr.MakeStub(ont_tcp_channel_process,ont_tcp_channel_process_hook);
    mgr.MakeStub(ont_tcp_channel_connect,ont_tcp_channel_connect_hook);
    mgr.MakeStub(ont_tcp_channel_write,ont_tcp_channel_write_hook);
    mgr.MakeStub(ont_tcp_channel_deinitilize,ont_tcp_channel_deinitilize_hook);
    ont_device_t *dev = (ont_device_t*)malloc(sizeof(ont_device_t));
    EXPECT_EQ(ONT_ERR_OK,ont_device_create(314,edp_type,"name",&dev));
    remove(devicefilename);
    EXPECT_EQ(ONT_ERR_OK,ont_device_connect(dev,"127.0.0.1",10019,"egSEGxef6s","123456",300));

    EXPECT_EQ(ONT_ERR_BADPARAM,ont_device_add_dp_int(dev,NULL,110));
    EXPECT_EQ(ONT_ERR_OK,ont_device_add_dp_string(dev,"2","string"));
    EXPECT_EQ(ONT_ERR_BADPARAM,ont_device_add_dp_binary(dev,NULL,"binary",6));
    EXPECT_EQ(ONT_ERR_OK,ont_device_add_dp_double(dev,"4",1.1));
    EXPECT_EQ(ONT_ERR_BADPARAM,ont_device_add_dp_object(dev,NULL,NULL));
    EXPECT_EQ(ONT_ERR_BADPARAM,ont_device_send_dp(dev));
    mgr.UnmakeStub(ont_tcp_channel_process);
    mgr.UnmakeStub(ont_device_get_rt);
    mgr.UnmakeStub(ont_tcp_channel_connect);
    mgr.UnmakeStub(ont_tcp_channel_write);
    mgr.UnmakeStub(ont_tcp_channel_deinitilize);
}
TEST_F(DeviceTest,ont_device_dp_clear_dp)
{
    DynamicStubManager mgr;
    mgr.MakeStub(ont_device_get_rt,ont_device_get_rt_hook);
    mgr.MakeStub(ont_tcp_channel_process,ont_tcp_channel_process_hook);
    mgr.MakeStub(ont_tcp_channel_connect,ont_tcp_channel_connect_hook);
    mgr.MakeStub(ont_tcp_channel_write,ont_tcp_channel_write_hook);
    mgr.MakeStub(ont_tcp_channel_deinitilize,ont_tcp_channel_deinitilize_hook);
    ont_device_t *dev = (ont_device_t*)malloc(sizeof(ont_device_t));
    EXPECT_EQ(ONT_ERR_OK,ont_device_create(314,edp_type,"name",&dev));
    remove(devicefilename);
    EXPECT_EQ(ONT_ERR_OK,ont_device_connect(dev,"127.0.0.1",10019,"egSEGxef6s","123456",300));

    EXPECT_EQ(ONT_ERR_OK,ont_device_add_dp_int(dev,"1",110));
    EXPECT_EQ(ONT_ERR_OK,ont_device_add_dp_string(dev,"2","string"));
    EXPECT_EQ(ONT_ERR_OK,ont_device_add_dp_binary(dev,"3","binary",6));
    EXPECT_EQ(ONT_ERR_OK,ont_device_add_dp_double(dev,"4",1.1));
    EXPECT_EQ(ONT_ERR_OK,ont_device_add_dp_object(dev,"5","{a:b}"));
 
    EXPECT_EQ(true,dev->formatter->buf != NULL);
    ont_device_clear_dp(dev);
    
    EXPECT_EQ(true,dev->formatter->buf == NULL);

    mgr.UnmakeStub(ont_tcp_channel_process);
    mgr.UnmakeStub(ont_device_get_rt);
    mgr.UnmakeStub(ont_tcp_channel_connect);
    mgr.UnmakeStub(ont_tcp_channel_write);
    mgr.UnmakeStub(ont_tcp_channel_deinitilize);
}
TEST_F(DeviceTest,ont_device_get_cmd)
{
    DynamicStubManager mgr;
    mgr.MakeStub(ont_device_get_rt,ont_device_get_rt_hook);
    mgr.MakeStub(ont_tcp_channel_process,ont_tcp_channel_process_hook);
    mgr.MakeStub(ont_tcp_channel_connect,ont_tcp_channel_connect_hook);
    mgr.MakeStub(ont_tcp_channel_write,ont_tcp_channel_write_hook);
    mgr.MakeStub(ont_tcp_channel_deinitilize,ont_tcp_channel_deinitilize_hook);
    ont_device_t *dev = (ont_device_t*)malloc(sizeof(ont_device_t));
    EXPECT_EQ(ONT_ERR_OK,ont_device_create(314,edp_type,"name",&dev));
/* normal */
    EXPECT_EQ(true,ont_device_get_cmd(dev)!=NULL); 
/* invalid param */
    EXPECT_EQ(true,ont_device_get_cmd(NULL)==NULL); 
    mgr.UnmakeStub(ont_tcp_channel_process);
    mgr.UnmakeStub(ont_device_get_rt);
    mgr.UnmakeStub(ont_tcp_channel_connect);
    mgr.UnmakeStub(ont_tcp_channel_write);
    mgr.UnmakeStub(ont_tcp_channel_deinitilize);

}
TEST_F(DeviceTest,ont_device_reply_cmd)
{
    DynamicStubManager mgr;
    mgr.MakeStub(ont_device_get_rt,ont_device_get_rt_hook);
    mgr.MakeStub(ont_tcp_channel_process,ont_tcp_channel_process_hook);
    mgr.MakeStub(ont_tcp_channel_connect,ont_tcp_channel_connect_hook);
    mgr.MakeStub(ont_tcp_channel_write,ont_tcp_channel_write_hook);
    mgr.MakeStub(ont_tcp_channel_deinitilize,ont_tcp_channel_deinitilize_hook);
    ont_device_t *dev = (ont_device_t*)malloc(sizeof(ont_device_t));
    EXPECT_EQ(ONT_ERR_OK,ont_device_create(314,edp_type,"name",&dev));
/* normal */
    EXPECT_EQ(ONT_ERR_OK,ont_device_reply_cmd(dev,"315","RESP",4));
/* invalid param */
    EXPECT_EQ(ONT_ERR_BADPARAM,ont_device_reply_cmd(NULL,"315","RESP",4));
    EXPECT_EQ(ONT_ERR_BADPARAM,ont_device_reply_cmd(dev,"315",NULL,4));
    EXPECT_EQ(ONT_ERR_OK,ont_device_reply_cmd(dev,"315","RESP",0));
    mgr.UnmakeStub(ont_tcp_channel_process);
    mgr.UnmakeStub(ont_device_get_rt);
    mgr.UnmakeStub(ont_tcp_channel_connect);
    mgr.UnmakeStub(ont_tcp_channel_write);
    mgr.UnmakeStub(ont_tcp_channel_deinitilize);

}
TEST_F(DeviceTest,ont_device_cmd_destroy)
{
    DynamicStubManager mgr;
    mgr.MakeStub(ont_device_get_rt,ont_device_get_rt_hook);
    mgr.MakeStub(ont_tcp_channel_process,ont_tcp_channel_process_hook);
    mgr.MakeStub(ont_tcp_channel_connect,ont_tcp_channel_connect_hook);
    mgr.MakeStub(ont_tcp_channel_write,ont_tcp_channel_write_hook);
    mgr.MakeStub(ont_tcp_channel_deinitilize,ont_tcp_channel_deinitilize_hook);
    ont_device_t *dev = (ont_device_t*)malloc(sizeof(ont_device_t));
    EXPECT_EQ(ONT_ERR_OK,ont_device_create(314,edp_type,"name",&dev));

    ont_device_cmd_t *cmd_t = ont_device_get_cmd(dev);

/* branch 1*/
    ont_device_cmd_destroy(NULL);
/* branch 2*/
    ont_device_cmd_destroy(cmd_t);
    cmd_t = NULL; 
    mgr.UnmakeStub(ont_tcp_channel_process);
    mgr.UnmakeStub(ont_device_get_rt);
    mgr.UnmakeStub(ont_tcp_channel_connect);
    mgr.UnmakeStub(ont_tcp_channel_write);
    mgr.UnmakeStub(ont_tcp_channel_deinitilize);

}
TEST_F(DeviceTest,ont_device_keepalive)
{
    DynamicStubManager mgr;
    mgr.MakeStub(ont_device_get_rt,ont_device_get_rt_hook);
    mgr.MakeStub(ont_tcp_channel_process,ont_tcp_channel_process_hook);
    mgr.MakeStub(ont_tcp_channel_connect,ont_tcp_channel_connect_hook);
    mgr.MakeStub(ont_tcp_channel_write,ont_tcp_channel_write_hook);
    mgr.MakeStub(ont_tcp_channel_deinitilize,ont_tcp_channel_deinitilize_hook);
    ont_device_t *dev = (ont_device_t*)malloc(sizeof(ont_device_t));
    EXPECT_EQ(ONT_ERR_OK,ont_device_create(314,edp_type,"name",&dev));
/* normal */
    EXPECT_EQ(ONT_ERR_OK,ont_device_keepalive(dev));    
/* badparam */
    EXPECT_EQ(ONT_ERR_BADPARAM,ont_device_keepalive(NULL)); 
    mgr.UnmakeStub(ont_tcp_channel_process);
    mgr.UnmakeStub(ont_device_get_rt);
    mgr.UnmakeStub(ont_tcp_channel_connect);
    mgr.UnmakeStub(ont_tcp_channel_write);
    mgr.UnmakeStub(ont_tcp_channel_deinitilize);

}
TEST_F(DeviceTest,ont_device_disconnect)
{
    DynamicStubManager mgr;
    mgr.MakeStub(ont_device_get_rt,ont_device_get_rt_hook);
    mgr.MakeStub(ont_tcp_channel_process,ont_tcp_channel_process_hook);
    mgr.MakeStub(ont_tcp_channel_connect,ont_tcp_channel_connect_hook);
    mgr.MakeStub(ont_tcp_channel_write,ont_tcp_channel_write_hook);
    mgr.MakeStub(ont_tcp_channel_deinitilize,ont_tcp_channel_deinitilize_hook);
    ont_device_t *dev = (ont_device_t*)malloc(sizeof(ont_device_t));
    EXPECT_EQ(ONT_ERR_OK,ont_device_create(314,edp_type,"name",&dev));
    remove(devicefilename);
    EXPECT_EQ(ONT_ERR_OK,ont_device_connect(dev,"127.0.0.1",10019,"egSEGxef6s","123456",300));
    EXPECT_EQ(true,(0==dev->exit));
    ont_device_disconnect(dev);
    EXPECT_EQ(false,(0==dev->exit));
    mgr.UnmakeStub(ont_tcp_channel_process);
    mgr.UnmakeStub(ont_device_get_rt);
    mgr.UnmakeStub(ont_tcp_channel_connect);
    mgr.UnmakeStub(ont_tcp_channel_write);
    mgr.UnmakeStub(ont_tcp_channel_deinitilize);

}

