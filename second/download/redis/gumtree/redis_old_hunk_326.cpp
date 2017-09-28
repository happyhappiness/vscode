         * to createSentinelRedisInstance(), otherwise we may trigger a
         * DNS lookup at runtime. */
        if (anetResolveIP(NULL,c->argv[3]->ptr,buf,sizeof(buf)) == ANET_ERR) {
            addReplyError(c,"Invalid IP address specified");
            return;
        }
        if (createSentinelRedisInstance(c->argv[2]->ptr,SRI_MASTER,
                c->argv[3]->ptr,port,quorum,NULL) == NULL)
        {
            switch(errno) {
            case EBUSY:
                addReplyError(c,"Duplicated master name");
                break;
            case EINVAL:
                addReplyError(c,"Invalid port number");
