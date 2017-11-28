bool
Ip::Address::setIPv4()
{
    if ( isLocalhost() ) {
        mSocketAddr_.sin6_addr = v4_localhost;
        return true;
    }

    if ( isAnyAddr() ) {
        mSocketAddr_.sin6_addr = v4_anyaddr;
        return true;
    }

    if ( isNoAddr() ) {
        mSocketAddr_.sin6_addr = v4_noaddr;
        return true;
    }

    if ( isIPv4())
        return true;

    // anything non-IPv4 and non-convertable is BAD.
    return false;
}