#ifndef NANOMSG_PROTOPUB_HPP
#define NANOMSG_PROTOPUB_HPP

#include "nanomsg_pub.hpp"


template<class T>
class nanomsg_ProtoPub : public nanomsg_pub
{
public:
    nanomsg_ProtoPub(string addr, int timeout_ms = 100)
        :nanomsg_pub(addr, timeout_ms)
    {

    }

    ~nanomsg_ProtoPub()
    {
        printf("%s\n", __func__);
    }

    bool sendProto(T& pro)
    {
        bool bRet = false;
        int size = pro.ByteSizeLong();;

        char* buf = new char[size];

        if( buf )
        {
            pro.SerializeToArray(buf, size);

            this->send(buf, size);

            delete[] buf;
            bRet = true;
        }

        return bRet;
    }

private:
    int nanomsg_sock;
    mutex send_mutex;
};
#endif // NANOMSG_PROTOPUB_HPP
