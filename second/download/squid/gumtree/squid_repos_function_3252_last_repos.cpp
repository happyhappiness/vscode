void
Ip::Qos::getTosFromServer(const Comm::ConnectionPointer &server, fde *clientFde)
{
#if USE_QOS_TOS && _SQUID_LINUX_
    /* Bug 2537: This part of ZPH only applies to patched Linux kernels. */
    tos_t tos = 1;
    int tos_len = sizeof(tos);
    clientFde->tosFromServer = 0;
    if (setsockopt(server->fd,SOL_IP,IP_RECVTOS,&tos,tos_len)==0) {
        unsigned char buf[512];
        int len = 512;
        if (getsockopt(server->fd,SOL_IP,IP_PKTOPTIONS,buf,(socklen_t*)&len) == 0) {
            /* Parse the PKTOPTIONS structure to locate the TOS data message
             * prepared in the kernel by the ZPH incoming TCP TOS preserving
             * patch.
             */
            unsigned char * pbuf = buf;
            while (pbuf-buf < len) {
                struct cmsghdr *o = (struct cmsghdr*)pbuf;
                if (o->cmsg_len<=0)
                    break;

                if (o->cmsg_level == SOL_IP && o->cmsg_type == IP_TOS) {
                    int *tmp = (int*)SQUID_CMSG_DATA(o);
                    clientFde->tosFromServer = (tos_t)*tmp;
                    break;
                }
                pbuf += CMSG_LEN(o->cmsg_len);
            }
        } else {
            int xerrno = errno;
            debugs(33, DBG_IMPORTANT, "QOS: error in getsockopt(IP_PKTOPTIONS) on " << server << " " << xstrerr(xerrno));
        }
    } else {
        int xerrno = errno;
        debugs(33, DBG_IMPORTANT, "QOS: error in setsockopt(IP_RECVTOS) on " << server << " " << xstrerr(xerrno));
    }
#endif
}