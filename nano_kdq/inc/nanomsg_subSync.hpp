#ifndef NANOMSG_SUB_SYNC_HPP
#define NANOMSG_SUB_SYNC_HPP

#include <nn.h>
#include <reqrep.h>
#include <pubsub.h>
#include <string>
#include <assert.h>
#include <mutex>
#include <thread>
#include <unistd.h>
#include <iostream>
#include "nanomsg_subBase.hpp"


class Nanomsg_SubSync : public Nanomsg_SubBase
{
public:
    Nanomsg_SubSync(string addr, string name, int timeout_ms = 100)
        :Nanomsg_SubBase(addr, name, timeout_ms)
    {

    }

    virtual ~Nanomsg_SubSync()
    {
        printf("%s\n", __func__);
    }

    bool Received(char &buf, int &bufsize )
    {
        int ret = false;

        if(this->nanomsg_sock >= 0)
        {
            char  *data = nullptr;
            int size = nn_recv(this->nanomsg_sock, &data, NN_MSG, 0);

            if(size < 1)
            {
//                printf("%s, nanomsg_sock[%d] recv failed! size[%d]\n",this->getName().c_str(),this->nanomsg_sock, size);
            }
            else
            {
                if(bufsize < size )
                {
                    printf("ERROR: %s buf is too small!! buf size[%d] recv size[%d]\n", this->getName().c_str(), bufsize, size);
                }
                else
                {
                    memcpy(&buf, data, size);
                    bufsize = size;
                    ret = true;
                }

                nn_freemsg (data);
            }

        }

        return ret;
    }

};

#endif // NANOMSG_SUB_ASYN_HPP
