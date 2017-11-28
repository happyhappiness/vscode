void
Auth::User::removeIp(Ip::Address ipaddr)
{
    AuthUserIP *ipdata = (AuthUserIP *) ip_list.head;

    while (ipdata) {
        /* walk the ip list */

        if (ipdata->ipaddr == ipaddr) {
            /* remove the node */
            dlinkDelete(&ipdata->node, &ip_list);
            delete ipdata;
            /* catch incipient underflow */
            assert(ipcount);
            -- ipcount;
            return;
        }

        ipdata = (AuthUserIP *) ipdata->node.next;
    }

}