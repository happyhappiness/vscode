void
Ip::Address::getSockAddr(struct sockaddr_in &buf) const
{
    if ( isIPv4() ) {
        buf.sin_family = AF_INET;
        buf.sin_port = mSocketAddr_.sin6_port;
        map6to4( mSocketAddr_.sin6_addr, buf.sin_addr);
    } else {
        debugs(14, DBG_CRITICAL, HERE << "Ip::Address::getSockAddr : Cannot convert non-IPv4 to IPv4. from " << *this );

        memset(&buf,0xFFFFFFFF,sizeof(struct sockaddr_in));
        assert(false);
    }

#if HAVE_SIN_LEN_IN_SAI
    /* not all OS have this field, BUT when they do it can be a problem if set wrong */
    buf.sin_len = sizeof(struct sockaddr_in);
#endif
}