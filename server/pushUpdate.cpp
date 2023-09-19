#include <iostream>
#include <string>
#include <linux/limits.h>
#include<sys/types.h>  
#include<sys/ipc.h>  
#include<sys/msg.h>  
#include <cstring>


 struct updateMsg{  
         long int msg_type;  
         char msg[PATH_MAX];  
 };  

int main(int argc, char** argv)  
{  
        int running=1;  
        int msgid;  
        struct updateMsg updMsg;  
        if (argc < 2)
        {
            std::cout<<"usage is different. TODO"<<std::endl;
            return 0;
        }
        char buffer[50]; //array to store user input  
        msgid=msgget((key_t)12346,0666|IPC_CREAT);  
        if (msgid == -1) // -1 means the message queue is not created  
        {  
                printf("Error in creating queue\n");  
                exit(0);  
        }  

        updMsg.msg_type=1;  
        strncpy(updMsg.msg,argv[1], sizeof(updMsg.msg));  
        if(msgsnd(msgid,(void *)&updMsg, sizeof(updateMsg),0)==-1) // msgsnd returns -1 if the message is not sent  
        {  
             printf("Msg not sent\n");  
        }  

}
