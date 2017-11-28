void
Auth::User::clearIp()
{
    AuthUserIP *ipdata, *tempnode;

    ipdata = (AuthUserIP *) ip_list.head;

    while (ipdata) {
        tempnode = (AuthUserIP *) ipdata->node.next;
        /* walk the ip list */
        dlinkDelete(&ipdata->node, &ip_list);
        cbdataFree(ipdata);
        /* catch incipient underflow */
        assert(ipcount);
        -- ipcount;
        ipdata = tempnode;
    }

    /* integrity check */
    assert(ipcount == 0);
}