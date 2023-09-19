#include <iostream>
#include <string>
#include <ActionReceiver.hpp>

using namespace std;

class ActionHandler : public ActionReceiver
{
    public:
        bool executeAction()
        {
            bool res = false;
            if (actionType == 0)
            {
                res = callPrintVersion();
            }
            else
                std::cout<<"Invalid Action Type"<<std::endl;
            return res;
        }
        bool callPrintVersion()
        {
            std::cout<<"Major = "<<majorVersion<<std::endl;
            std::cout<<"Minor = "<<minorVersion<<std::endl;
            std::cout<<"productName = "<<productName<<std::endl;
            return true;
        }
    private:
        int majorVersion = 8;
        int minorVersion = 6;
        string productName = {"nxtgen"} ;
};

extern "C" 
{
    ActionHandler* createActionHandler()
    {
        return new ActionHandler();
    }

    void destroyActionHandler(ActionHandler *v)
    {
        delete v;
    }
}


