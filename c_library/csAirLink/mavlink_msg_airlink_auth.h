//------------------------------
// The fastMavlink library
// (c) OlliW, OlliW42, www.olliw.eu
//------------------------------

#pragma once
#ifndef FASTMAVLINK_MSG_AIRLINK_AUTH_H
#define FASTMAVLINK_MSG_AIRLINK_AUTH_H


//----------------------------------------
//-- Message AIRLINK_AUTH
//----------------------------------------

// fields are ordered, as they appear on the wire
FASTMAVLINK_PACK(
typedef struct _fmav_airlink_auth_t {
    char login[50];
    char password[50];
}) fmav_airlink_auth_t;


#define FASTMAVLINK_MSG_ID_AIRLINK_AUTH  52000

#define FASTMAVLINK_MSG_AIRLINK_AUTH_PAYLOAD_LEN_MAX  100
#define FASTMAVLINK_MSG_AIRLINK_AUTH_CRCEXTRA  13

#define FASTMAVLINK_MSG_AIRLINK_AUTH_FLAGS  0
#define FASTMAVLINK_MSG_AIRLINK_AUTH_TARGET_SYSTEM_OFS  0
#define FASTMAVLINK_MSG_AIRLINK_AUTH_TARGET_COMPONENT_OFS  0

#define FASTMAVLINK_MSG_AIRLINK_AUTH_FRAME_LEN_MAX  125

#define FASTMAVLINK_MSG_AIRLINK_AUTH_FIELD_LOGIN_NUM  50 // number of elements in array
#define FASTMAVLINK_MSG_AIRLINK_AUTH_FIELD_LOGIN_LEN  50 // length of array = number of bytes
#define FASTMAVLINK_MSG_AIRLINK_AUTH_FIELD_PASSWORD_NUM  50 // number of elements in array
#define FASTMAVLINK_MSG_AIRLINK_AUTH_FIELD_PASSWORD_LEN  50 // length of array = number of bytes

#define FASTMAVLINK_MSG_AIRLINK_AUTH_FIELD_LOGIN_OFS  0
#define FASTMAVLINK_MSG_AIRLINK_AUTH_FIELD_PASSWORD_OFS  50


//----------------------------------------
//-- Message AIRLINK_AUTH pack,encode routines, for sending
//----------------------------------------

FASTMAVLINK_FUNCTION_DECORATOR uint16_t fmav_msg_airlink_auth_pack(
    fmav_message_t* _msg,
    uint8_t sysid,
    uint8_t compid,
    const char* login, const char* password,
    fmav_status_t* _status)
{
    fmav_airlink_auth_t* _payload = (fmav_airlink_auth_t*)_msg->payload;


    memcpy(&(_payload->login), login, sizeof(char)*50);
    memcpy(&(_payload->password), password, sizeof(char)*50);

    _msg->sysid = sysid;
    _msg->compid = compid;
    _msg->msgid = FASTMAVLINK_MSG_ID_AIRLINK_AUTH;
    _msg->target_sysid = 0;
    _msg->target_compid = 0;
    _msg->crc_extra = FASTMAVLINK_MSG_AIRLINK_AUTH_CRCEXTRA;
    _msg->payload_max_len = FASTMAVLINK_MSG_AIRLINK_AUTH_PAYLOAD_LEN_MAX;

    return fmav_finalize_msg(_msg, _status);
}


FASTMAVLINK_FUNCTION_DECORATOR uint16_t fmav_msg_airlink_auth_encode(
    fmav_message_t* _msg,
    uint8_t sysid,
    uint8_t compid,
    const fmav_airlink_auth_t* _payload,
    fmav_status_t* _status)
{
    return fmav_msg_airlink_auth_pack(
        _msg, sysid, compid,
        _payload->login, _payload->password,
        _status);
}


FASTMAVLINK_FUNCTION_DECORATOR uint16_t fmav_msg_airlink_auth_pack_to_frame_buf(
    uint8_t* _buf,
    uint8_t sysid,
    uint8_t compid,
    const char* login, const char* password,
    fmav_status_t* _status)
{
    fmav_airlink_auth_t* _payload = (fmav_airlink_auth_t*)(&_buf[FASTMAVLINK_HEADER_V2_LEN]);


    memcpy(&(_payload->login), login, sizeof(char)*50);
    memcpy(&(_payload->password), password, sizeof(char)*50);

    _buf[5] = sysid;
    _buf[6] = compid;
    _buf[7] = (uint8_t)FASTMAVLINK_MSG_ID_AIRLINK_AUTH;
    _buf[8] = ((uint32_t)FASTMAVLINK_MSG_ID_AIRLINK_AUTH >> 8);
    _buf[9] = ((uint32_t)FASTMAVLINK_MSG_ID_AIRLINK_AUTH >> 16);

    return fmav_finalize_frame_buf(
        _buf,
        FASTMAVLINK_MSG_AIRLINK_AUTH_PAYLOAD_LEN_MAX,
        FASTMAVLINK_MSG_AIRLINK_AUTH_CRCEXTRA,
        _status);
}


FASTMAVLINK_FUNCTION_DECORATOR uint16_t fmav_msg_airlink_auth_encode_to_frame_buf(
    uint8_t* _buf,
    uint8_t sysid,
    uint8_t compid,
    const fmav_airlink_auth_t* _payload,
    fmav_status_t* _status)
{
    return fmav_msg_airlink_auth_pack_to_frame_buf(
        _buf, sysid, compid,
        _payload->login, _payload->password,
        _status);
}


#ifdef FASTMAVLINK_SERIAL_WRITE_CHAR

FASTMAVLINK_FUNCTION_DECORATOR uint16_t fmav_msg_airlink_auth_pack_to_serial(
    uint8_t sysid,
    uint8_t compid,
    const char* login, const char* password,
    fmav_status_t* _status)
{
    fmav_airlink_auth_t _payload;


    memcpy(&(_payload.login), login, sizeof(char)*50);
    memcpy(&(_payload.password), password, sizeof(char)*50);

    return fmav_finalize_serial(
        sysid,
        compid,
        (uint8_t*)&_payload,
        FASTMAVLINK_MSG_ID_AIRLINK_AUTH,
        FASTMAVLINK_MSG_AIRLINK_AUTH_PAYLOAD_LEN_MAX,
        FASTMAVLINK_MSG_AIRLINK_AUTH_CRCEXTRA,
        _status);
}


FASTMAVLINK_FUNCTION_DECORATOR uint16_t fmav_msg_airlink_auth_encode_to_serial(
    uint8_t sysid,
    uint8_t compid,
    const fmav_airlink_auth_t* _payload,
    fmav_status_t* _status)
{
    return fmav_finalize_serial(
        sysid,
        compid,
        (uint8_t*)_payload,
        FASTMAVLINK_MSG_ID_AIRLINK_AUTH,
        FASTMAVLINK_MSG_AIRLINK_AUTH_PAYLOAD_LEN_MAX,
        FASTMAVLINK_MSG_AIRLINK_AUTH_CRCEXTRA,
        _status);
}
#endif


//----------------------------------------
//-- Message AIRLINK_AUTH decode routines, for receiving
//----------------------------------------
// For these functions to work correctly, the msg payload must be zero-filled.
// Call the helper fmav_msg_zerofill() if needed, or set FASTMAVLINK_ALWAYS_ZEROFILL to 1
// Note that the parse functions do zero-fill the msg payload, but that message generator functions
// do not. This means that for the msg obtained from parsing the below functions can safely be used,
// but that this is not so for the msg obtained from pack/encode functions.

FASTMAVLINK_FUNCTION_DECORATOR void fmav_msg_airlink_auth_decode(fmav_airlink_auth_t* payload, const fmav_message_t* msg)
{
#if FASTMAVLINK_ALWAYS_ZEROFILL
    if (msg->len < FASTMAVLINK_MSG_AIRLINK_AUTH_PAYLOAD_LEN_MAX) {
        memcpy(payload, msg->payload, msg->len);
        // ensure that returned payload is zero-filled
        memset(&(((uint8_t*)payload)[msg->len]), 0, FASTMAVLINK_MSG_AIRLINK_AUTH_PAYLOAD_LEN_MAX - msg->len);
    } else {
        // note: msg->len can be larger than PAYLOAD_LEN_MAX if the message has unknown extensions
        memcpy(payload, msg->payload, FASTMAVLINK_MSG_AIRLINK_AUTH_PAYLOAD_LEN_MAX);
    }
#else
    // this requires that msg payload had been zero-filled before
    memcpy(payload, msg->payload, FASTMAVLINK_MSG_AIRLINK_AUTH_PAYLOAD_LEN_MAX);
#endif
}





FASTMAVLINK_FUNCTION_DECORATOR char* fmav_msg_airlink_auth_get_field_login_ptr(const fmav_message_t* msg)
{
    return (char*)&(msg->payload[0]);
}


FASTMAVLINK_FUNCTION_DECORATOR char fmav_msg_airlink_auth_get_field_login(uint16_t index, const fmav_message_t* msg)
{
    if (index >= FASTMAVLINK_MSG_AIRLINK_AUTH_FIELD_LOGIN_NUM) return 0;
    return ((char*)&(msg->payload[0]))[index];
}


FASTMAVLINK_FUNCTION_DECORATOR char* fmav_msg_airlink_auth_get_field_password_ptr(const fmav_message_t* msg)
{
    return (char*)&(msg->payload[50]);
}


FASTMAVLINK_FUNCTION_DECORATOR char fmav_msg_airlink_auth_get_field_password(uint16_t index, const fmav_message_t* msg)
{
    if (index >= FASTMAVLINK_MSG_AIRLINK_AUTH_FIELD_PASSWORD_NUM) return 0;
    return ((char*)&(msg->payload[50]))[index];
}


//----------------------------------------
//-- Pymavlink wrappers
//----------------------------------------
#ifdef FASTMAVLINK_PYMAVLINK_ENABLED

#define MAVLINK_MSG_ID_AIRLINK_AUTH  52000

#define mavlink_airlink_auth_t  fmav_airlink_auth_t

#define MAVLINK_MSG_ID_AIRLINK_AUTH_LEN  100
#define MAVLINK_MSG_ID_AIRLINK_AUTH_MIN_LEN  100
#define MAVLINK_MSG_ID_52000_LEN  100
#define MAVLINK_MSG_ID_52000_MIN_LEN  100

#define MAVLINK_MSG_ID_AIRLINK_AUTH_CRC  13
#define MAVLINK_MSG_ID_52000_CRC  13

#define MAVLINK_MSG_AIRLINK_AUTH_FIELD_LOGIN_LEN 50
#define MAVLINK_MSG_AIRLINK_AUTH_FIELD_PASSWORD_LEN 50


#if MAVLINK_COMM_NUM_BUFFERS > 0

FASTMAVLINK_FUNCTION_DECORATOR uint16_t mavlink_msg_airlink_auth_pack(
    uint8_t sysid,
    uint8_t compid,
    mavlink_message_t* _msg,
    const char* login, const char* password)
{
    fmav_status_t* _status = mavlink_get_channel_status(MAVLINK_COMM_0);
    return fmav_msg_airlink_auth_pack(
        _msg, sysid, compid,
        login, password,
        _status);
}


FASTMAVLINK_FUNCTION_DECORATOR uint16_t mavlink_msg_airlink_auth_encode(
    uint8_t sysid,
    uint8_t compid,
    mavlink_message_t* _msg,
    const mavlink_airlink_auth_t* _payload)
{
    return mavlink_msg_airlink_auth_pack(
        sysid,
        compid,
        _msg,
        _payload->login, _payload->password);
}

#endif


FASTMAVLINK_FUNCTION_DECORATOR uint16_t mavlink_msg_airlink_auth_pack_txbuf(
    char* _buf,
    fmav_status_t* _status,
    uint8_t sysid,
    uint8_t compid,
    const char* login, const char* password)
{
    return fmav_msg_airlink_auth_pack_to_frame_buf(
        (uint8_t*)_buf,
        sysid,
        compid,
        login, password,
        _status);
}


FASTMAVLINK_FUNCTION_DECORATOR void mavlink_msg_airlink_auth_decode(const mavlink_message_t* msg, mavlink_airlink_auth_t* payload)
{
    fmav_msg_airlink_auth_decode(payload, msg);
}

#endif // FASTMAVLINK_PYMAVLINK_ENABLED


#endif // FASTMAVLINK_MSG_AIRLINK_AUTH_H
