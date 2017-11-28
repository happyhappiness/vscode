char* IpAddress::NtoA(char* buf, const unsigned int blen, int force) const
{
    // Ensure we have a buffer.
    if (buf == NULL) {
        return NULL;
    }

    /* some external code may have blindly memset a parent. */
    /* thats okay, our default is known */
    if ( IsAnyAddr() ) {
        memcpy(buf,"::\0", min(static_cast<unsigned int>(3),blen));
        return buf;
    }

    memset(buf,0,blen); // clear buffer before write

    /* Pure-IPv6 CANNOT be displayed in IPv4 format. */
    /* However IPv4 CAN. */
    if ( force == AF_INET && !IsIPv4() ) {
        if ( IsIPv6() ) {
            memcpy(buf, "{!IPv4}\0", min(static_cast<unsigned int>(8),blen));
        }
        return buf;
    }

    if ( force == AF_INET6 || (force == AF_UNSPEC && IsIPv6()) ) {

        xinet_ntop(AF_INET6, &m_SocketAddr.sin6_addr, buf, blen);

    } else  if ( force == AF_INET || (force == AF_UNSPEC && IsIPv4()) ) {

        struct in_addr tmp;
        GetInAddr(tmp);
        xinet_ntop(AF_INET, &tmp, buf, blen);
    } else {
        debugs(14,0,"WARNING: Corrupt IP Address details OR required to display in unknown format (" <<
               force << "). accepted={" << AF_UNSPEC << "," << AF_INET << "," << AF_INET6 << "}");
        fprintf(stderr,"WARNING: Corrupt IP Address details OR required to display in unknown format (%d). accepted={%d,%d,%d} ",
                force, AF_UNSPEC, AF_INET, AF_INET6);
        memcpy(buf,"dead:beef::\0", min(static_cast<unsigned int>(13),blen));
        assert(false);
    }

    return buf;
}