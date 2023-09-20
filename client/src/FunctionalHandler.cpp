#include <string>
#include <unistd.h>

#define BUFSIZE 1024

/* dlopen */
#include <gnu/lib-names.h>
#include <dlfcn.h>
#include <ActionReceiver.hpp>
#include <pthread.h>

/* Function : PrintSoftwareVersion
 * Desc     : Printing version using dlopen of upgraded software
 * Input    : None
 * Output   : None
 */
void PrintSoftwareVersion()
{
    void *handle;
    char *error;
    const char *FileName = "./libfunctional.so";

    /* dlopen to open the file */
    handle = dlopen(FileName, RTLD_LAZY);
    if (!handle) {
        std::cerr<<"Error opening file : "<<dlerror()<<std::endl;
        return;
    }
    /* clear existing errors. */
    dlerror();  

    create_t *CreateFunction = (create_t *) dlsym(handle, "createActionHandler");

    if ((error = dlerror()) != NULL)  {
        std::cerr<<"Symbol not found : "<<dlerror()<<std::endl;
        dlclose(handle);
        return;
    }

    destroy_t *DeleteFunction = (destroy_t *) dlsym(handle, "destroyActionHandler");

    if ((error = dlerror()) != NULL)  {
        std::cerr<<"Symbol not found : "<<dlerror()<<std::endl;
        dlclose(handle);
        return;
    }
    ActionReceiver *actRecv = CreateFunction();

    actRecv->setActionType(0);

    actRecv->executeAction();

    DeleteFunction(actRecv);
    
    dlclose(handle);

}

