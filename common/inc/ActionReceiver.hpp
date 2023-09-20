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
#ifdef DEBUG
            std::cout<<"Action Template1 constructor called"<<stendl;
#endif
        }
        void setActionType(int argActionType)
        {
            actionType = argActionType;
        }
        virtual bool executeAction() = 0;
        virtual ~ActionReceiver()
        {
#ifdef DEBUG
            std::cout<<"Action Template1 destructor called"<<std::endl;
#endif
        }
};

typedef ActionReceiver* create_t();
typedef void destroy_t(ActionReceiver *);
