#ifndef NANOMSG_SUB_BASE_HPP
#define NANOMSG_SUB_BASE_HPP

#include <nn.h>
#include <reqrep.h>
#include <pubsub.h>
#include <string>
#include <assert.h>
#include <mutex>
#include <thread>
#include <unistd.h>
#include <iostream>

using namespace  std;

typedef void (*__callback)(char* buff, size_t size);

class Nanomsg_SubBase
{
public:
    Nanomsg_SubBase(string addr, string name,int timeout_ms = 100)
        :nanomsg_sock(-1)
    {
        int rv = -1;

        nanomsg_sock = nn_socket(AF_SP, NN_SUB);
        assert(nanomsg_sock >= 0);

        rv = nn_setsockopt(nanomsg_sock, NN_SUB, NN_SUB_SUBSCRIBE, "", 0);
        assert(rv >=0);

        // set timeout
        rv = nn_setsockopt(nanomsg_sock, 0, NN_RCVTIMEO, &timeout_ms, sizeof(timeout_ms));
        assert(rv >= 0);

        rv = nn_connect(nanomsg_sock, addr.c_str());
        assert(rv >= 0);

        sub_name = name;

    }

    virtual ~Nanomsg_SubBase()
    {
        printf("%s\n", __func__);

        if( nanomsg_sock >= 0 )
        {
            nn_close(nanomsg_sock);
        }
    }

    string& getName()
    {
        return sub_name;
    }

protected:

    int nanomsg_sock;
    string sub_name;
};

#endif // NANOMSG_SUB_BASE_HPP
