static unsigned int find_if_index(const apr_sockaddr_t *iface)
{
    unsigned int index = 0;
#if defined(HAVE_GETIFADDRS) && APR_HAVE_IPV6 
    struct ifaddrs *ifp, *ifs;

    /**
     * TODO: getifaddrs is only portable to *BSD and OS X. Using ioctl 
     *       and SIOCGIFCONF is needed for Linux/Solaris support.
     *       
     *       There is a wrapper that takes the messy ioctl interface into 
     *       getifaddrs. The license is acceptable, but, It is a fairly large 
     *       chunk of code.
     */
    if (getifaddrs(&ifs) != 0) {
        return 0;
    }

    for (ifp = ifs; ifp; ifp = ifp->ifa_next) {
        if (ifp->ifa_addr != NULL && ifp->ifa_addr->sa_family == AF_INET6) {
            if (memcmp(&iface->sa.sin6.sin6_addr,
                       &ifp->ifa_addr->sa_data[0],
                       sizeof(iface->sa.sin6.sin6_addr)) == 0) {
                index = if_nametoindex(ifp->ifa_name);
                break;
            }
        }
    }

    freeifaddrs(ifs);
#endif
    return index;
}