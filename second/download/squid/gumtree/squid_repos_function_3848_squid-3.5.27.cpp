char *
Ip::Address::toStr(char* buf, const unsigned int blen, int force) const
{
    // Ensure we have a buffer.
    if (buf == NULL) {
        return NULL;
    }

    /* some external code may have blindly memset a parent. */
    /* thats okay, our default is known */
    if ( isAnyAddr() ) {
        if (isIPv6())
            memcpy(buf,"::\0", min(static_cast<unsigned int>(3),blen));
        else if (isIPv4())
            memcpy(buf,"0.0.0.0\0", min(static_cast<unsigned int>(8),blen));
        return buf;
    }

    memset(buf,0,blen); // clear buffer before write

    /* Pure-IPv6 CANNOT be displayed in IPv4 format. */
    /* However IPv4 CAN. */
    if ( force == AF_INET && !isIPv4() ) {
        if ( isIPv6() ) {
            memcpy(buf, "{!IPv4}\0", min(static_cast<unsigned int>(8),blen));
        }
        return buf;
    }

    if ( force == AF_INET6 || (force == AF_UNSPEC && isIPv6()) ) {

        inet_ntop(AF_INET6, &mSocketAddr_.sin6_addr, buf, blen);

    } else  if ( force == AF_INET || (force == AF_UNSPEC && isIPv4()) ) {

        struct in_addr tmp;
        getInAddr(tmp);
        inet_ntop(AF_INET, &tmp, buf, blen);
    } else {
        debugs(14, DBG_CRITICAL, "WARNING: Corrupt IP Address details OR required to display in unknown format (" <<
               force << "). accepted={" << AF_UNSPEC << "," << AF_INET << "," << AF_INET6 << "}");
        fprintf(stderr,"WARNING: Corrupt IP Address details OR required to display in unknown format (%d). accepted={%d,%d,%d} ",
                force, AF_UNSPEC, AF_INET, AF_INET6);
        memcpy(buf,"dead:beef::\0", min(static_cast<unsigned int>(13),blen));
        assert(false);
    }

    return buf;
}