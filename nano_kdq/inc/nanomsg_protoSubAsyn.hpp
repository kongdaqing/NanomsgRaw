#ifndef NANOMSG_SUBPROTOASYN_HPP
#define NANOMSG_SUBPROTOASYN_HPP

#include "nanomsg_subAsyn.hpp"

template<class T>
class Nanomsg_ProtoSubAsyn : public Nanomsg_SubAsyn
{
public:
    Nanomsg_ProtoSubAsyn(string addr, string name , int timeout_ms = 100)
        :Nanomsg_SubAsyn(addr, name, timeout_ms)
    {}

    ~Nanomsg_ProtoSubAsyn()
    {
        printf("%s\n", __func__);
    }

    void OnReceived(char* data, size_t size)
    {
        if(data && size)
        {
            T msg;

            if( !msg.ParseFromArray(data, static_cast<int>(size)) )
            {
                // drop uncompelete recevied data
                printf(" ERROR: %s Parse failed! drop size:%zu \n", sub_name.c_str(), size);
            }
            else
            {
                OnProtoReceived(msg);

            }
        }
    }

protected:

    virtual void OnProtoReceived(T& msg) = 0;
};

#endif // NANOMSG_SUBPROTOASYN_HPP
