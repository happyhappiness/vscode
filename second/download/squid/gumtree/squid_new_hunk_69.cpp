    hash_first(proxy_auth_username_cache);

    while ((usernamehash = ((AuthUserHashPointer *) hash_next(proxy_auth_username_cache)))) {
        auth_user = usernamehash->user();
        /* free cached acl results */
        aclCacheMatchFlush(&auth_user->proxy_match_cache);
    }

    debugs(29, 3, HERE << "Finished.");
}

void
Auth::User::cacheCleanup(void *datanotused)
{
    /*
     * We walk the hash by username as that is the unique key we use.
     * For big hashs we could consider stepping through the cache, 100/200
     * entries at a time. Lets see how it flys first.
     */
    AuthUserHashPointer *usernamehash;
    Auth::User::Pointer auth_user;
    char const *username = NULL;
    debugs(29, 3, HERE << "Cleaning the user cache now");
    debugs(29, 3, HERE << "Current time: " << current_time.tv_sec);
    hash_first(proxy_auth_username_cache);

    while ((usernamehash = ((AuthUserHashPointer *) hash_next(proxy_auth_username_cache)))) {
        auth_user = usernamehash->user();
        username = auth_user->username();

        /* if we need to have indedendent expiry clauses, insert a module call
         * here */
        debugs(29, 4, HERE << "Cache entry:\n\tType: " <<
               auth_user->auth_type << "\n\tUsername: " << username <<
               "\n\texpires: " <<
               (long int) (auth_user->expiretime + ::Config.authenticateTTL) <<
               "\n\treferences: " << (long int) auth_user->RefCountCount());

        if (auth_user->expiretime + ::Config.authenticateTTL <= current_time.tv_sec) {
            debugs(29, 5, HERE << "Removing user " << username << " from cache due to timeout.");

            /* Old credentials are always removed. Existing users must hold their own
             * Auth::User::Pointer to the credentials. Cache exists only for finding
             * and re-using current valid credentials.
             */
            hash_remove_link(proxy_auth_username_cache, usernamehash);
            delete usernamehash;
        }
    }

    debugs(29, 3, HERE << "Finished cleaning the user cache.");
    eventAdd("User Cache Maintenance", cacheCleanup, NULL, ::Config.authenticateGCInterval, 1);
    last_discard = squid_curtime;
}

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

void
Auth::User::removeIp(Ip::Address ipaddr)
{
    AuthUserIP *ipdata = (AuthUserIP *) ip_list.head;

    while (ipdata) {
        /* walk the ip list */

        if (ipdata->ipaddr == ipaddr) {
            /* remove the node */
            dlinkDelete(&ipdata->node, &ip_list);
            cbdataFree(ipdata);
            /* catch incipient underflow */
            assert(ipcount);
            -- ipcount;
            return;
        }

        ipdata = (AuthUserIP *) ipdata->node.next;
    }

}

void
Auth::User::addIp(Ip::Address ipaddr)
{
    AuthUserIP *ipdata = (AuthUserIP *) ip_list.head;
    int found = 0;

    CBDATA_INIT_TYPE(AuthUserIP);

    /*
     * we walk the entire list to prevent the first item in the list
     * preventing old entries being flushed and locking a user out after
     * a timeout+reconfigure
     */
    while (ipdata) {
        AuthUserIP *tempnode = (AuthUserIP *) ipdata->node.next;
        /* walk the ip list */

        if (ipdata->ipaddr == ipaddr) {
            /* This ip has already been seen. */
            found = 1;
            /* update IP ttl */
            ipdata->ip_expiretime = squid_curtime;
        } else if (ipdata->ip_expiretime + ::Config.authenticateIpTTL < squid_curtime) {
            /* This IP has expired - remove from the seen list */
            dlinkDelete(&ipdata->node, &ip_list);
            cbdataFree(ipdata);
            /* catch incipient underflow */
            assert(ipcount);
            -- ipcount;
        }

        ipdata = tempnode;
    }

    if (found)
        return;

    /* This ip is not in the seen list */
    ipdata = cbdataAlloc(AuthUserIP);

    ipdata->ip_expiretime = squid_curtime;

    ipdata->ipaddr = ipaddr;

    dlinkAddTail(ipdata, &ipdata->node, &ip_list);

    ipcount++;

    debugs(29, 2, HERE << "user '" << username() << "' has been seen at a new IP address (" << ipaddr << ")");
}

/**
 * Add the Auth::User structure to the username cache.
 */
void
Auth::User::addToNameCache()
{
    /* AuthUserHashPointer will self-register with the username cache */
    new AuthUserHashPointer(this);
}

/**
 * Dump the username cache statictics for viewing...
 */
void
Auth::User::UsernameCacheStats(StoreEntry *output)
{
    AuthUserHashPointer *usernamehash;

    /* overview of username cache */
    storeAppendPrintf(output, "Cached Usernames: %d of %d\n", proxy_auth_username_cache->count, proxy_auth_username_cache->size);
    storeAppendPrintf(output, "Next Garbage Collection in %d seconds.\n",
                      static_cast<int32_t>(last_discard + ::Config.authenticateGCInterval - squid_curtime));

    /* cache dump column titles */
    storeAppendPrintf(output, "\n%-15s %-9s %-9s %-9s %s\n",
                      "Type",
                      "State",
                      "Check TTL",
                      "Cache TTL",
                      "Username");
    storeAppendPrintf(output, "--------------- --------- --------- --------- ------------------------------\n");

    hash_first(proxy_auth_username_cache);
    while ((usernamehash = ((AuthUserHashPointer *) hash_next(proxy_auth_username_cache)))) {
        Auth::User::Pointer auth_user = usernamehash->user();

        storeAppendPrintf(output, "%-15s %-9s %-9d %-9d %s\n",
                          Auth::Type_str[auth_user->auth_type],
                          CredentialState_str[auth_user->credentials()],
                          auth_user->ttl(),
                          static_cast<int32_t>(auth_user->expiretime - squid_curtime + ::Config.authenticateTTL),
                          auth_user->username()
                         );
    }
}
