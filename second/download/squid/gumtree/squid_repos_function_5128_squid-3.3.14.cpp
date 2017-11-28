void
Auth::User::absorb(Auth::User::Pointer from)
{
    /*
     * XXX Incomplete: it should merge in hash references too and ask the module to merge in scheme data
     *  dlink_list proxy_auth_list;
     *  dlink_list proxy_match_cache;
     */

    debugs(29, 5, HERE << "auth_user '" << from << "' into auth_user '" << this << "'.");

    /* absorb the list of IP address sources (for max_user_ip controls) */
    AuthUserIP *new_ipdata;
    while (from->ip_list.head != NULL) {
        new_ipdata = static_cast<AuthUserIP *>(from->ip_list.head->data);

        /* If this IP has expired - ignore the expensive merge actions. */
        if (new_ipdata->ip_expiretime + ::Config.authenticateIpTTL < squid_curtime) {
            /* This IP has expired - remove from the source list */
            dlinkDelete(&new_ipdata->node, &(from->ip_list));
            cbdataFree(new_ipdata);
            /* catch incipient underflow */
            -- from->ipcount;
        } else {
            /* add to our list. replace if already present. */
            AuthUserIP *ipdata = static_cast<AuthUserIP *>(ip_list.head->data);
            bool found = false;
            while (ipdata) {
                AuthUserIP *tempnode = static_cast<AuthUserIP *>(ipdata->node.next->data);

                if (ipdata->ipaddr == new_ipdata->ipaddr) {
                    /* This IP has already been seen. */
                    found = true;
                    /* update IP ttl and stop searching. */
                    ipdata->ip_expiretime = max(ipdata->ip_expiretime, new_ipdata->ip_expiretime);
                    break;
                } else if (ipdata->ip_expiretime + ::Config.authenticateIpTTL < squid_curtime) {
                    /* This IP has expired - cleanup the destination list */
                    dlinkDelete(&ipdata->node, &ip_list);
                    cbdataFree(ipdata);
                    /* catch incipient underflow */
                    assert(ipcount);
                    -- ipcount;
                }

                ipdata = tempnode;
            }

            if (!found) {
                /* This ip is not in the seen list. Add it. */
                dlinkAddTail(&new_ipdata->node, &ipdata->node, &ip_list);
                ++ipcount;
                /* remove from the source list */
                dlinkDelete(&new_ipdata->node, &(from->ip_list));
                ++from->ipcount;
            }
        }
    }
}