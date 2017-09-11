            addReplyError(c,"Invalid IP address specified");
            return;
        }
        if (createSentinelRedisInstance(c->argv[2]->ptr,SRI_MASTER,
                c->argv[3]->ptr,port,quorum,NULL) == NULL)
        {
            switch(errno) {
            case EBUSY:
                addReplyError(c,"Duplicated master name");
