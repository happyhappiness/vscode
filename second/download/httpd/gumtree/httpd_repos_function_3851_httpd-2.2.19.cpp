static void fill_mip_v6(struct ipv6_mreq *mip, const apr_sockaddr_t *mcast,
                        const apr_sockaddr_t *iface)
{
    memcpy(&mip->ipv6mr_multiaddr, mcast->ipaddr_ptr,
           sizeof(mip->ipv6mr_multiaddr));

    if (iface == NULL) {
        mip->ipv6mr_interface = 0;
    }
    else {
        mip->ipv6mr_interface = find_if_index(iface);
    }
}