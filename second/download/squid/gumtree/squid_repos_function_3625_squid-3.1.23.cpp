int
IpIntercept::NetfilterTransparent(int fd, const IpAddress &me, IpAddress &client, int silent)
{
#if LINUX_NETFILTER

    /* Trust the user configured properly. If not no harm done.
     * We will simply attempt a bind outgoing on our own IP.
     */
    if (fd_table[fd].flags.transparent) {
        client.SetPort(0); // allow random outgoing port to prevent address clashes
        debugs(89, 5, HERE << "address TPROXY: me= " << me << ", client= " << client);
        return 0;
    }

    debugs(89, 9, HERE << "address: me= " << me << ", client= " << client);
#endif
    return -1;
}