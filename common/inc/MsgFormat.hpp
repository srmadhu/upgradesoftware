#pragma once 

#include <iostream>


#define BUFSIZE 1024

typedef enum
{
    MSG_SWDLFLNAME,
    MSG_SWDLFILE,
    MSG_SWDLCMPT,
    MSG_CLREGISTER,
    MSG_CLREGDONE,
    MSG_CLDEREGISTER
} MsgTypeEnum ;

typedef enum
{
    CL_STATE_INIT,
    CL_STATE_REGISTER,
    CL_STATE_REGDONE,
    CL_STATE_EXIT
} StateEnum;

#define PUSH_COMMAND "push"

#define FILE_LOCATION "/tmp"

typedef struct
{
    MsgTypeEnum msgType;
    char Buffer[BUFSIZE];
    int Length;
} UpdateMsg_t;
