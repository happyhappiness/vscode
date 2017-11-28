bool
Ip::Address::operator =(const struct addrinfo &s)
{

    struct sockaddr_in* ipv4 = NULL;

    struct sockaddr_in6* ipv6 = NULL;

    //struct addrinfo {
    //             int ai_flags;           /* input flags */
    //             int ai_family;          /* protocol family for socket */
    //             int ai_socktype;        /* socket type */
    //             int ai_protocol;        /* protocol for socket */
    //             socklen_t ai_addrlen;   /* length of socket-address */
    //             struct sockaddr *ai_addr; /* socket-address for socket */
    //             char *ai_canonname;     /* canonical name for service location */
    //             struct addrinfo *ai_next; /* pointer to next in list */
    //}

    switch (s.ai_family) {

    case AF_INET:
        ipv4 = (sockaddr_in*)(s.ai_addr);
        /* this */
        assert(ipv4);
        operator=(*ipv4);
        break;

    case AF_INET6:
        ipv6 = (sockaddr_in6*)(s.ai_addr);
        /* this */
        assert(ipv6);
        operator=(*ipv6);
        break;

    case AF_UNSPEC:
    default:
        // attempt to handle partially initialised addrinfo.
        // such as those where data only comes from getsockopt()
        if (s.ai_addr != NULL) {
            if (s.ai_addrlen == sizeof(struct sockaddr_in6)) {
                operator=(*((struct sockaddr_in6*)s.ai_addr));
                return true;
            } else if (s.ai_addrlen == sizeof(struct sockaddr_in)) {
                operator=(*((struct sockaddr_in*)s.ai_addr));
                return true;
            }
        }
        return false;
    }

    return true;
}