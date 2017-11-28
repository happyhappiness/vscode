bool
Ip::Address::operator =(const struct hostent &s)
{

    struct in_addr* ipv4 = NULL;

    struct in6_addr* ipv6 = NULL;

    //struct hostent {
    //        char    *h_name;        /* official name of host */
    //        char    **h_aliases;    /* alias list */
    //        int     h_addrtype;     /* host address type */
    //        int     h_length;       /* length of address */
    //        char    **h_addr_list;  /* list of addresses */
    //}

    switch (s.h_addrtype) {

    case AF_INET:
        ipv4 = (in_addr*)(s.h_addr_list[0]);
        /* this */
        operator=(*ipv4);
        break;

    case AF_INET6:
        ipv6 = (in6_addr*)(s.h_addr_list[0]);
        /* this */
        operator=(*ipv6);
        break;

    default:
        IASSERT("false",false);
        return false;
    }

    return true;
}