static void fill_mip_v4(struct ip_mreq *mip, apr_sockaddr_t *mcast,
                        apr_sockaddr_t *iface)
{
    mip->imr_multiaddr = mcast->sa.sin.sin_addr;
    if (iface == NULL) {
        mip->imr_interface.s_addr = INADDR_ANY;
    }
    else {
        mip->imr_interface = iface->sa.sin.sin_addr;
    }
}