/*
 * server_proto.h
 *
 *  Created on: 2016年3月3日
 *      Author: leiwenbin
 */

#ifndef SERVER_PROTO_H_
#define SERVER_PROTO_H_

#pragma pack(push)
#pragma pack(1)

#include "transport_proto.h"

#define COMMON_SERVER_LOGIN_REQ         0x10000100    //服务器登录请求
#define COMMON_SERVER_LOGIN_RET         0x10000101    //服务器登录返回

#define COMMON_CLIENT_LOGOUT_REQ        0x10000102    //客户端退出请求
#define COMMON_CLIENT_LOGOUT_RET        0x10000103    //客户端退出返回

#define COMMON_SYNC_HOST_REQ            0x10000104    //HOST同步SESSION

#define COMMON_MSG_EXCEPTION_REQ        0x10000106    //HOST消息发送发生异常

#define COMMON_PUSH_RADIO_MSG_RET       0x10000107    //在线广播消息
#define COMMON_PUSH_ALL_RADIO_MSG_RET   0x10000109    //全量广播消息

#define COMMON_CLIENT_EXCEPTION_REQ     0x10000110    //客户端再上线之前异常连接断开的消息

#define COMMON_CONSLOE_LOGIN_REQ        0x10000301    //CONSOLE控制台服务登录请求
#define COMMON_CONSLOE_LOGIN_RET        0x10000303    //CONSOLE控制台服务登录返回

#define COMMON_AGENT_LOST_RET           0x10000501    //AGENT已断开

//SERVER ROLE
typedef enum ServerRole {
    NONE = 0, CENTER_SERVER, HOST_SERVER, PUSH_SERVER, CONSOLE_SERVER
} SERVER_ROLE;

//目标类型
typedef enum TargetType {
    TARGET_CLIENT = 0, //终端
    TARGET_USER,       //帐户
    TARGET_MULTI       //终端+帐户
} TARGET_TYPE;

//推送类型
typedef enum PushType {
    PUSH_NONE = 0,
    PUSH_ALL,          //在线+离线
    PUSH_ONLINE        //在线
} PUSH_TYPE;

//回执类型
typedef enum ReceiptLv {
    NOT_NEED_RECEIPT = 0,       //不需要回执
    MUST_NEED_RECEIPT           //需要回执
} RECEIPT_LV;

typedef struct Target {
    char uid_key[128];
    char account_key[128];
    TARGET_TYPE target_type;
} TARGET;

typedef struct Targets {
    uint32_t target_count;
    Target target[0];
} TARGETS;

typedef struct PushMsg {
    long long int failure_time;
    long long int send_time;
    char product[32];
    char msg_id[64];
    RECEIPT_LV receipt_lv;
    PUSH_TYPE push_type;
    uint32_t msg_len;
    char msg_buf[0];
} PUSH_MSG;

typedef struct SvrInfo {
    char ip[32];
    uint32_t port;
    uint32_t connection_count;
    uint32_t connection_max;
    uint32_t client_count;
    uint32_t user_count;
    char area[32];
    char isp[32];
    uint32_t load;
    uint32_t memory_used;
    uint32_t online;
    ServerRole svr_role;
    long long timestamp;
} SVR_INFO;

typedef struct HostSession {
    uint32_t have_user;
    char uid_key[128];
    char account_key[128];
} HOST_SESSION;

typedef struct DataBlock {
    uint32_t block_len;
    char product[128];
    char block_buf[0];
} DATA_BLOCK;

typedef enum MsgError {
    SEND_SUCCESS = 0x00,
    CLIENT_NOT_FOUND,
    SEND_ERROR,
    /* retry error 3~7 */
    NOT_RECEIPT = 0x08,
    CONVERT_OFFLINE
} MSG_ERROR;

typedef struct MsgException {
    TARGET target;
    MSG_ERROR msg_error;
    PUSH_MSG push_msg;
} MSG_EXCEPTION;

typedef struct MsgReceiptVal {
    char msg_id[64];
    TARGET target;
} MSG_RECEIPT_VAL;

#pragma pack(pop)

#endif /* SERVER_PROTO_H_ */
