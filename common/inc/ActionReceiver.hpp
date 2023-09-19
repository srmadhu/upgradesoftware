#pragma once 
#include <iostream>
#include <string>


class ActionReceiver
{
    protected:
        int actionType;

    public:
        ActionReceiver(): actionType (0)
        {
            std::cout<<"Action Template constructor called"<<std::endl;
        }
        void setActionType(int argActionType)
        {
            actionType = argActionType;
        }
        virtual bool executeAction() = 0;
        virtual ~ActionReceiver()
        {
            std::cout<<"Action Template destructor called"<<std::endl;
        }
};

typedef ActionReceiver* create_t();
typedef void destroy_t(ActionReceiver *);
