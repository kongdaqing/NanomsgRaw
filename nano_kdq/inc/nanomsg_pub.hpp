#ifndef NANOMSG_PUB_HPP
#define NANOMSG_PUB_HPP

#include <nn.h>
#include <reqrep.h>
#include <pubsub.h>
#include <string>
#include <assert.h>
#include <mutex>

using namespace  std;

class nanomsg_pub
{
public:
    nanomsg_pub(string addr, int timeout_ms = 100)
        :nanomsg_sock(-1)
    {
        int rv = -1;

        nanomsg_sock = nn_socket(AF_SP, NN_PUB);
        assert(nanomsg_sock >= 0);

        rv = nn_bind(nanomsg_sock, addr.c_str());
        assert(rv >= 0);

        // set timeout
        rv = nn_setsockopt(nanomsg_sock, 0, NN_SNDTIMEO, &timeout_ms, sizeof(timeout_ms));
        assert(rv >= 0);
    }

    ~nanomsg_pub()
    {
        if( nanomsg_sock >= 0 )
        {
            nn_close(nanomsg_sock);
        }
    }

    int send(const char* data, size_t size)
    {
        int ret = -1;

        send_mutex.lock();

        if( nanomsg_sock >= 0 )
        {
            ret = nn_send(nanomsg_sock, data, size, 0);
            assert (ret == size);
        }

        send_mutex.unlock();

        return ret;
    }

private:
    int nanomsg_sock;
    mutex send_mutex;
};
#endif // NANOMSG_PUB_HPP
