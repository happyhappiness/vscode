void
AuthUser::clearIp()
{
    auth_user_ip_t *ipdata, *tempnode;

    ipdata = (auth_user_ip_t *) ip_list.head;

    while (ipdata) {
        tempnode = (auth_user_ip_t *) ipdata->node.next;
        /* walk the ip list */
        dlinkDelete(&ipdata->node, &ip_list);
        cbdataFree(ipdata);
        /* catch incipient underflow */
        assert(ipcount);
        ipcount--;
        ipdata = tempnode;
    }

    /* integrity check */
    assert(ipcount == 0);
}