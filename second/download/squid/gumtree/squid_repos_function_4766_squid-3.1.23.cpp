void
AuthUser::removeIp(IpAddress ipaddr)
{
    auth_user_ip_t *ipdata = (auth_user_ip_t *) ip_list.head;

    while (ipdata) {
        /* walk the ip list */

        if (ipdata->ipaddr == ipaddr) {
            /* remove the node */
            dlinkDelete(&ipdata->node, &ip_list);
            cbdataFree(ipdata);
            /* catch incipient underflow */
            assert(ipcount);
            ipcount--;
            return;
        }

        ipdata = (auth_user_ip_t *) ipdata->node.next;
    }

}