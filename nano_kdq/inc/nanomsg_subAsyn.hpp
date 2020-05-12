#ifndef NANOMSG_SUB_ASYN_HPP
#define NANOMSG_SUB_ASYN_HPP

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

using namespace  std;

typedef void (*__callback)(char* buff, size_t size);

class Nanomsg_SubAsyn : public Nanomsg_SubBase
{
public:
    Nanomsg_SubAsyn(string addr, string name , int timeout_ms = 100)
        :Nanomsg_SubBase(addr, name, timeout_ms)
    {
        if( nanomsg_sock >= 0 )
        {
            auto sub = std::thread([&]() { this->sub_thread(); });
            sub.detach();
        }
    }

    ~Nanomsg_SubAsyn()
    {
        printf("%s\n", __func__);
    }

private:

    void sub_thread() {

              while (this->nanomsg_sock >= 0) {

                      char  *data = nullptr;
                      int size = nn_recv(this->nanomsg_sock, &data, NN_MSG, 0);
                      if(size < 1) {
//                          printf("%s: nanomsg_sock[%d] recv failed! size[%d]\n",this->getName().c_str(),this->nanomsg_sock, size);
                          usleep(3000);
                          continue;
                      }

                      this->recv_callback(data, size);

                      nn_freemsg (data);
                  }

    }

    void recv_callback(char* buff, size_t size)
    {
        this->OnReceived(buff, size);
    }

    virtual void OnReceived(char* data, size_t size) = 0;

};

#endif // NANOMSG_SUB_ASYN_HPP
