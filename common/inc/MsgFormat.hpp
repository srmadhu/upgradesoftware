#pragma once 

#include <iostream>


#define BUFSIZE 1024

typedef enum
{
    MSG_FILENAME,
    MSG_SENDFILE,
    MSG_FILEEND,
    MSG_REGISTER,
    MSG_REGDONE,
    MSG_DEREGISTER
} MsgTypeEnum ;

typedef enum
{
    STATE_INIT,
    STATE_REGISTER,
    STATE_REGDONE,
    STATE_EXIT
} StateEnum;

#define PUSH_COMMAND "push"

#define FILE_LOCATION "/tmp"

typedef struct
{
    MsgTypeEnum msgType;
    char Buffer[BUFSIZE];
    int Length;
} UpdateMsg_t;
