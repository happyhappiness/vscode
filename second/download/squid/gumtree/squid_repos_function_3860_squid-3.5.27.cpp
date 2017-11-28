void Ip::Qos::getNfmarkFromServer(const Comm::ConnectionPointer &server, const fde *clientFde)
{
#if USE_LIBNETFILTERCONNTRACK
    /* Allocate a new conntrack */
    if (struct nf_conntrack *ct = nfct_new()) {

        /* Prepare data needed to find the connection in the conntrack table.
         * We need the local and remote IP address, and the local and remote
         * port numbers.
         */

        if (Ip::EnableIpv6 && server->local.isIPv6()) {
            nfct_set_attr_u8(ct, ATTR_L3PROTO, AF_INET6);
            struct in6_addr serv_fde_remote_ip6;
            server->remote.getInAddr(serv_fde_remote_ip6);
            nfct_set_attr(ct, ATTR_IPV6_DST, serv_fde_remote_ip6.s6_addr);
            struct in6_addr serv_fde_local_ip6;
            server->local.getInAddr(serv_fde_local_ip6);
            nfct_set_attr(ct, ATTR_IPV6_SRC, serv_fde_local_ip6.s6_addr);
        } else {
            nfct_set_attr_u8(ct, ATTR_L3PROTO, AF_INET);
            struct in_addr serv_fde_remote_ip;
            server->remote.getInAddr(serv_fde_remote_ip);
            nfct_set_attr_u32(ct, ATTR_IPV4_DST, serv_fde_remote_ip.s_addr);
            struct in_addr serv_fde_local_ip;
            server->local.getInAddr(serv_fde_local_ip);
            nfct_set_attr_u32(ct, ATTR_IPV4_SRC, serv_fde_local_ip.s_addr);
        }

        nfct_set_attr_u8(ct, ATTR_L4PROTO, IPPROTO_TCP);
        nfct_set_attr_u16(ct, ATTR_PORT_DST, htons(server->remote.port()));
        nfct_set_attr_u16(ct, ATTR_PORT_SRC, htons(server->local.port()));

        /* Open a handle to the conntrack */
        if (struct nfct_handle *h = nfct_open(CONNTRACK, 0)) {
            /* Register the callback. The callback function will record the mark value. */
            nfct_callback_register(h, NFCT_T_ALL, getNfMarkCallback, (void *)clientFde);
            /* Query the conntrack table using the data previously set */
            int x = nfct_query(h, NFCT_Q_GET, ct);
            if (x == -1) {
                debugs(17, 2, "QOS: Failed to retrieve connection mark: (" << x << ") " << strerror(errno)
                       << " (Destination " << server->remote << ", source " << server->local << ")" );
            }
            nfct_close(h);
        } else {
            debugs(17, 2, "QOS: Failed to open conntrack handle for upstream netfilter mark retrieval.");
        }
        nfct_destroy(ct);

    } else {
        debugs(17, 2, "QOS: Failed to allocate new conntrack for upstream netfilter mark retrieval.");
    }
#endif
}