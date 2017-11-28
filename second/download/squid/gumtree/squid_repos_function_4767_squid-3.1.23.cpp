void
AuthUser::addIp(IpAddress ipaddr)
{
    auth_user_ip_t *ipdata = (auth_user_ip_t *) ip_list.head;
    int found = 0;

    CBDATA_INIT_TYPE(auth_user_ip_t);

    /*
     * we walk the entire list to prevent the first item in the list
     * preventing old entries being flushed and locking a user out after
     * a timeout+reconfigure
     */
    while (ipdata) {
        auth_user_ip_t *tempnode = (auth_user_ip_t *) ipdata->node.next;
        /* walk the ip list */

        if (ipdata->ipaddr == ipaddr) {
            /* This ip has already been seen. */
            found = 1;
            /* update IP ttl */
            ipdata->ip_expiretime = squid_curtime;
        } else if (ipdata->ip_expiretime + Config.authenticateIpTTL < squid_curtime) {
            /* This IP has expired - remove from the seen list */
            dlinkDelete(&ipdata->node, &ip_list);
            cbdataFree(ipdata);
            /* catch incipient underflow */
            assert(ipcount);
            ipcount--;
        }

        ipdata = tempnode;
    }

    if (found)
        return;

    /* This ip is not in the seen list */
    ipdata = cbdataAlloc(auth_user_ip_t);

    ipdata->ip_expiretime = squid_curtime;

    ipdata->ipaddr = ipaddr;

    dlinkAddTail(ipdata, &ipdata->node, &ip_list);

    ipcount++;

    debugs(29, 2, "authenticateAuthUserAddIp: user '" << username() << "' has been seen at a new IP address (" << ipaddr << ")");
}