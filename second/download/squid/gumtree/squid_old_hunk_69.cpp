    hash_first(proxy_auth_username_cache);

    while ((usernamehash = ((AuthUserHashPointer *) hash_next(proxy_auth_username_cache)))) {
        auth_user = usernamehash->user();
        /* free cached acl results */
        aclCacheMatchFlush(&auth_user->proxy_match_cache);

    }

    debugs(29, 3, "AuthUser::CachedACLsReset: Finished.");
}

void
AuthUser::cacheCleanup(void *datanotused)
{
    /*
     * We walk the hash by username as that is the unique key we use.
     * For big hashs we could consider stepping through the cache, 100/200
     * entries at a time. Lets see how it flys first.
     */
    AuthUserHashPointer *usernamehash;
    AuthUser *auth_user;
    char const *username = NULL;
    debugs(29, 3, "AuthUser::cacheCleanup: Cleaning the user cache now");
    debugs(29, 3, "AuthUser::cacheCleanup: Current time: " << current_time.tv_sec);
    hash_first(proxy_auth_username_cache);

    while ((usernamehash = ((AuthUserHashPointer *) hash_next(proxy_auth_username_cache)))) {
        auth_user = usernamehash->user();
        username = auth_user->username();

        /* if we need to have inpedendent expiry clauses, insert a module call
         * here */
        debugs(29, 4, "AuthUser::cacheCleanup: Cache entry:\n\tType: " <<
               auth_user->auth_type << "\n\tUsername: " << username <<
               "\n\texpires: " <<
               (long int) (auth_user->expiretime + Config.authenticateTTL) <<
               "\n\treferences: " << (long int) auth_user->references);

        if (auth_user->expiretime + Config.authenticateTTL <= current_time.tv_sec) {
            debugs(29, 5, "AuthUser::cacheCleanup: Removing user " << username << " from cache due to timeout.");
            /* the minus 1 accounts for the cache lock */

            if (!(authenticateAuthUserInuse(auth_user) - 1))
                /* we don't warn if we leave the user in the cache,
                 * because other modules (ie delay pools) may keep
                 * locks on users, and thats legitimate
                 */
                auth_user->unlock();
        }
    }

    debugs(29, 3, "AuthUser::cacheCleanup: Finished cleaning the user cache.");
    eventAdd("User Cache Maintenance", cacheCleanup, NULL, Config.authenticateGCInterval, 1);
}

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


void
AuthUser::lock()
{
    debugs(29, 9, "authenticateAuthUserLock auth_user '" << this << "'.");
    assert(this != NULL);
    references++;
    debugs(29, 9, "authenticateAuthUserLock auth_user '" << this << "' now at '" << references << "'.");
}

void
AuthUser::unlock()
{
    debugs(29, 9, "authenticateAuthUserUnlock auth_user '" << this << "'.");
    assert(this != NULL);

    if (references > 0) {
        references--;
    } else {
        debugs(29, 1, "Attempt to lower Auth User " << this << " refcount below 0!");
    }

    debugs(29, 9, "authenticateAuthUserUnlock auth_user '" << this << "' now at '" << references << "'.");

    if (references == 0)
        delete this;
}

/* addToNameCache: add a auth_user structure to the username cache */
void
AuthUser::addToNameCache()
{
    usernamehash = new AuthUserHashPointer (this);
}
