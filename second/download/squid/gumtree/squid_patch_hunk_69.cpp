     hash_first(proxy_auth_username_cache);
 
     while ((usernamehash = ((AuthUserHashPointer *) hash_next(proxy_auth_username_cache)))) {
         auth_user = usernamehash->user();
         /* free cached acl results */
         aclCacheMatchFlush(&auth_user->proxy_match_cache);
-
     }
 
-    debugs(29, 3, "AuthUser::CachedACLsReset: Finished.");
+    debugs(29, 3, HERE << "Finished.");
 }
 
 void
-AuthUser::cacheCleanup(void *datanotused)
+Auth::User::cacheCleanup(void *datanotused)
 {
     /*
      * We walk the hash by username as that is the unique key we use.
      * For big hashs we could consider stepping through the cache, 100/200
      * entries at a time. Lets see how it flys first.
      */
     AuthUserHashPointer *usernamehash;
-    AuthUser *auth_user;
+    Auth::User::Pointer auth_user;
     char const *username = NULL;
-    debugs(29, 3, "AuthUser::cacheCleanup: Cleaning the user cache now");
-    debugs(29, 3, "AuthUser::cacheCleanup: Current time: " << current_time.tv_sec);
+    debugs(29, 3, HERE << "Cleaning the user cache now");
+    debugs(29, 3, HERE << "Current time: " << current_time.tv_sec);
     hash_first(proxy_auth_username_cache);
 
     while ((usernamehash = ((AuthUserHashPointer *) hash_next(proxy_auth_username_cache)))) {
         auth_user = usernamehash->user();
         username = auth_user->username();
 
-        /* if we need to have inpedendent expiry clauses, insert a module call
+        /* if we need to have indedendent expiry clauses, insert a module call
          * here */
-        debugs(29, 4, "AuthUser::cacheCleanup: Cache entry:\n\tType: " <<
+        debugs(29, 4, HERE << "Cache entry:\n\tType: " <<
                auth_user->auth_type << "\n\tUsername: " << username <<
                "\n\texpires: " <<
-               (long int) (auth_user->expiretime + Config.authenticateTTL) <<
-               "\n\treferences: " << (long int) auth_user->references);
+               (long int) (auth_user->expiretime + ::Config.authenticateTTL) <<
+               "\n\treferences: " << (long int) auth_user->RefCountCount());
 
-        if (auth_user->expiretime + Config.authenticateTTL <= current_time.tv_sec) {
-            debugs(29, 5, "AuthUser::cacheCleanup: Removing user " << username << " from cache due to timeout.");
-            /* the minus 1 accounts for the cache lock */
-
-            if (!(authenticateAuthUserInuse(auth_user) - 1))
-                /* we don't warn if we leave the user in the cache,
-                 * because other modules (ie delay pools) may keep
-                 * locks on users, and thats legitimate
-                 */
-                auth_user->unlock();
+        if (auth_user->expiretime + ::Config.authenticateTTL <= current_time.tv_sec) {
+            debugs(29, 5, HERE << "Removing user " << username << " from cache due to timeout.");
+
+            /* Old credentials are always removed. Existing users must hold their own
+             * Auth::User::Pointer to the credentials. Cache exists only for finding
+             * and re-using current valid credentials.
+             */
+            hash_remove_link(proxy_auth_username_cache, usernamehash);
+            delete usernamehash;
         }
     }
 
-    debugs(29, 3, "AuthUser::cacheCleanup: Finished cleaning the user cache.");
-    eventAdd("User Cache Maintenance", cacheCleanup, NULL, Config.authenticateGCInterval, 1);
+    debugs(29, 3, HERE << "Finished cleaning the user cache.");
+    eventAdd("User Cache Maintenance", cacheCleanup, NULL, ::Config.authenticateGCInterval, 1);
+    last_discard = squid_curtime;
 }
 
 void
-AuthUser::clearIp()
+Auth::User::clearIp()
 {
-    auth_user_ip_t *ipdata, *tempnode;
+    AuthUserIP *ipdata, *tempnode;
 
-    ipdata = (auth_user_ip_t *) ip_list.head;
+    ipdata = (AuthUserIP *) ip_list.head;
 
     while (ipdata) {
-        tempnode = (auth_user_ip_t *) ipdata->node.next;
+        tempnode = (AuthUserIP *) ipdata->node.next;
         /* walk the ip list */
         dlinkDelete(&ipdata->node, &ip_list);
         cbdataFree(ipdata);
         /* catch incipient underflow */
         assert(ipcount);
-        ipcount--;
+        -- ipcount;
         ipdata = tempnode;
     }
 
     /* integrity check */
     assert(ipcount == 0);
 }
 
 void
-AuthUser::removeIp(IpAddress ipaddr)
+Auth::User::removeIp(Ip::Address ipaddr)
 {
-    auth_user_ip_t *ipdata = (auth_user_ip_t *) ip_list.head;
+    AuthUserIP *ipdata = (AuthUserIP *) ip_list.head;
 
     while (ipdata) {
         /* walk the ip list */
 
         if (ipdata->ipaddr == ipaddr) {
             /* remove the node */
             dlinkDelete(&ipdata->node, &ip_list);
             cbdataFree(ipdata);
             /* catch incipient underflow */
             assert(ipcount);
-            ipcount--;
+            -- ipcount;
             return;
         }
 
-        ipdata = (auth_user_ip_t *) ipdata->node.next;
+        ipdata = (AuthUserIP *) ipdata->node.next;
     }
 
 }
 
 void
-AuthUser::addIp(IpAddress ipaddr)
+Auth::User::addIp(Ip::Address ipaddr)
 {
-    auth_user_ip_t *ipdata = (auth_user_ip_t *) ip_list.head;
+    AuthUserIP *ipdata = (AuthUserIP *) ip_list.head;
     int found = 0;
 
-    CBDATA_INIT_TYPE(auth_user_ip_t);
+    CBDATA_INIT_TYPE(AuthUserIP);
 
     /*
      * we walk the entire list to prevent the first item in the list
      * preventing old entries being flushed and locking a user out after
      * a timeout+reconfigure
      */
     while (ipdata) {
-        auth_user_ip_t *tempnode = (auth_user_ip_t *) ipdata->node.next;
+        AuthUserIP *tempnode = (AuthUserIP *) ipdata->node.next;
         /* walk the ip list */
 
         if (ipdata->ipaddr == ipaddr) {
             /* This ip has already been seen. */
             found = 1;
             /* update IP ttl */
             ipdata->ip_expiretime = squid_curtime;
-        } else if (ipdata->ip_expiretime + Config.authenticateIpTTL < squid_curtime) {
+        } else if (ipdata->ip_expiretime + ::Config.authenticateIpTTL < squid_curtime) {
             /* This IP has expired - remove from the seen list */
             dlinkDelete(&ipdata->node, &ip_list);
             cbdataFree(ipdata);
             /* catch incipient underflow */
             assert(ipcount);
-            ipcount--;
+            -- ipcount;
         }
 
         ipdata = tempnode;
     }
 
     if (found)
         return;
 
     /* This ip is not in the seen list */
-    ipdata = cbdataAlloc(auth_user_ip_t);
+    ipdata = cbdataAlloc(AuthUserIP);
 
     ipdata->ip_expiretime = squid_curtime;
 
     ipdata->ipaddr = ipaddr;
 
     dlinkAddTail(ipdata, &ipdata->node, &ip_list);
 
     ipcount++;
 
-    debugs(29, 2, "authenticateAuthUserAddIp: user '" << username() << "' has been seen at a new IP address (" << ipaddr << ")");
+    debugs(29, 2, HERE << "user '" << username() << "' has been seen at a new IP address (" << ipaddr << ")");
 }
 
-
+/**
+ * Add the Auth::User structure to the username cache.
+ */
 void
-AuthUser::lock()
+Auth::User::addToNameCache()
 {
-    debugs(29, 9, "authenticateAuthUserLock auth_user '" << this << "'.");
-    assert(this != NULL);
-    references++;
-    debugs(29, 9, "authenticateAuthUserLock auth_user '" << this << "' now at '" << references << "'.");
+    /* AuthUserHashPointer will self-register with the username cache */
+    new AuthUserHashPointer(this);
 }
 
+/**
+ * Dump the username cache statictics for viewing...
+ */
 void
-AuthUser::unlock()
+Auth::User::UsernameCacheStats(StoreEntry *output)
 {
-    debugs(29, 9, "authenticateAuthUserUnlock auth_user '" << this << "'.");
-    assert(this != NULL);
-
-    if (references > 0) {
-        references--;
-    } else {
-        debugs(29, 1, "Attempt to lower Auth User " << this << " refcount below 0!");
-    }
+    AuthUserHashPointer *usernamehash;
 
-    debugs(29, 9, "authenticateAuthUserUnlock auth_user '" << this << "' now at '" << references << "'.");
+    /* overview of username cache */
+    storeAppendPrintf(output, "Cached Usernames: %d of %d\n", proxy_auth_username_cache->count, proxy_auth_username_cache->size);
+    storeAppendPrintf(output, "Next Garbage Collection in %d seconds.\n",
+                      static_cast<int32_t>(last_discard + ::Config.authenticateGCInterval - squid_curtime));
+
+    /* cache dump column titles */
+    storeAppendPrintf(output, "\n%-15s %-9s %-9s %-9s %s\n",
+                      "Type",
+                      "State",
+                      "Check TTL",
+                      "Cache TTL",
+                      "Username");
+    storeAppendPrintf(output, "--------------- --------- --------- --------- ------------------------------\n");
 
-    if (references == 0)
-        delete this;
-}
+    hash_first(proxy_auth_username_cache);
+    while ((usernamehash = ((AuthUserHashPointer *) hash_next(proxy_auth_username_cache)))) {
+        Auth::User::Pointer auth_user = usernamehash->user();
 
-/* addToNameCache: add a auth_user structure to the username cache */
-void
-AuthUser::addToNameCache()
-{
-    usernamehash = new AuthUserHashPointer (this);
+        storeAppendPrintf(output, "%-15s %-9s %-9d %-9d %s\n",
+                          Auth::Type_str[auth_user->auth_type],
+                          CredentialState_str[auth_user->credentials()],
+                          auth_user->ttl(),
+                          static_cast<int32_t>(auth_user->expiretime - squid_curtime + ::Config.authenticateTTL),
+                          auth_user->username()
+                         );
+    }
 }
