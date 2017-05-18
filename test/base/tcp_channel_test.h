#define CHECK_TCP_CHANNEL_T_PARA(iface)                         \
    EXPECT_EQ(iface.fn_initilize, ont_tcp_channel_initilize);\
    EXPECT_EQ(iface.fn_deinitilize, ont_tcp_channel_deinitilize);\
    EXPECT_EQ(iface.fn_write, ont_tcp_channel_write);\
    EXPECT_EQ(iface.fn_process, ont_tcp_channel_process);\
    EXPECT_EQ(iface.fn_connect, ont_tcp_channel_connect);\
    \
    tcp_channel_t* tc = (tcp_channel_t*)iface.channel;          \
    EXPECT_EQ(1024, tc->buffer_in.end - tc->buffer_in.begin);\
    EXPECT_EQ(tc->buffer_in.begin, tc->buffer_in.current);\
    EXPECT_EQ(1024, tc->buffer_out.end - tc->buffer_out.begin);\
    EXPECT_EQ(tc->buffer_out.begin, tc->buffer_out.current);\
    \
    EXPECT_EQ(0, strcmp(tc->addr, g_ip.c_str()));   \
    EXPECT_EQ(tc->port, g_port);\
    EXPECT_EQ(0, strcmp((char*)tc->owner_ctx, owner_ctx));\
    EXPECT_EQ(tc->timeout, 1000);\
    \
    EXPECT_EQ(&iface, tc->channel)

#define CHECK_TCP_CHANNEL_T_PARA_CB(iface, read_packet_cb)                     \
    EXPECT_EQ(iface.fn_initilize, ont_tcp_channel_initilize);           \
    EXPECT_EQ(iface.fn_deinitilize, ont_tcp_channel_deinitilize);\
    EXPECT_EQ(iface.fn_write, ont_tcp_channel_write);\
    EXPECT_EQ(iface.fn_process, ont_tcp_channel_process);\
    EXPECT_EQ(iface.fn_connect, ont_tcp_channel_connect);\
    \
    tcp_channel_t* tc = (tcp_channel_t*)iface.channel;          \
    EXPECT_EQ(1024, tc->buffer_in.end - tc->buffer_in.begin);\
    EXPECT_EQ(tc->buffer_in.begin, tc->buffer_in.current);\
    EXPECT_EQ(1024, tc->buffer_out.end - tc->buffer_out.begin);\
    EXPECT_EQ(tc->buffer_out.begin, tc->buffer_out.current);\
    \
    EXPECT_EQ(0, strcmp(tc->addr, g_ip.c_str()));   \
    EXPECT_EQ(tc->port, g_port);\
    EXPECT_STREQ(NULL, (char*)tc->owner_ctx);        \
    EXPECT_EQ(tc->timeout, 1000);\
    \
    EXPECT_EQ(read_packet_cb , iface.fn_cb_read_packet);\
    EXPECT_EQ(&iface, tc->channel);



#define CHECK_TCP_CHANNEL_T_PARA_CB_CTX(iface, read_packet_cb, owner_ctx)     \
    EXPECT_EQ(iface.fn_initilize, ont_tcp_channel_initilize);\
    EXPECT_EQ(iface.fn_deinitilize, ont_tcp_channel_deinitilize);\
    EXPECT_EQ(iface.fn_write, ont_tcp_channel_write);\
    EXPECT_EQ(iface.fn_process, ont_tcp_channel_process);\
    EXPECT_EQ(iface.fn_connect, ont_tcp_channel_connect);\
    \
    tcp_channel_t* tc = (tcp_channel_t*)iface.channel;          \
    EXPECT_EQ(1024, tc->buffer_in.end - tc->buffer_in.begin);\
    EXPECT_EQ(tc->buffer_in.begin, tc->buffer_in.current);\
    EXPECT_EQ(1024, tc->buffer_out.end - tc->buffer_out.begin);\
    EXPECT_EQ(tc->buffer_out.begin, tc->buffer_out.current);\
    \
    EXPECT_EQ(0, strcmp(tc->addr, g_ip.c_str()));   \
    EXPECT_EQ(tc->port, g_port);\
    EXPECT_EQ(0, strcmp((char*)tc->owner_ctx, owner_ctx));\
    EXPECT_EQ(tc->timeout, 1000);\
    \
    EXPECT_EQ(read_packet_cb , iface.fn_cb_read_packet);\
    EXPECT_EQ(&iface, tc->channel)


typedef struct MsgNode{
    char *m_send_buf;
    size_t m_send_size;
    char *m_recv_buf;
    size_t m_recv_size;
}MsgNode_t;
