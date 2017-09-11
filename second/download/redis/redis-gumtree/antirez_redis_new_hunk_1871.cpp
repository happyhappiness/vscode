        /* Make sure the IP field is actually a valid IP before passing it
         * to createSentinelRedisInstance(), otherwise we may trigger a
         * DNS lookup at runtime. */
        if (anetResolveIP(NULL,c->argv[3]->ptr,ip,sizeof(ip)) == ANET_ERR) {
            addReplyError(c,"Invalid IP address specified");
            return;
        }
