#ifndef NANOMSG_PROTOSUBSYNC_H
#define NANOMSG_PROTOSUBSYNC_H

#include "nanomsg_subSync.hpp"


template<class T>
class Nanomsg_ProtoSubSync : public Nanomsg_SubSync
{
public:
    Nanomsg_ProtoSubSync(string addr, string name , int timeout_ms = 100)
        :Nanomsg_SubSync(addr, name, timeout_ms)
    {}

    ~Nanomsg_ProtoSubSync()
    {
        printf("%s\n", __func__);
    }

    bool ProtoReceived(T& pro )
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
                if( !pro.ParseFromArray(data, static_cast<int>(size)) )
                {
                    // drop uncompelete recevied data
                    printf(" ERROR: %s Parse failed! drop size:%zu \n", sub_name.c_str(), size);
                }

                nn_freemsg (data);
                ret = true;
            }

        }

        return ret;
    }

};


#endif // NANOMSG_PROTOSUBSYNC_H
