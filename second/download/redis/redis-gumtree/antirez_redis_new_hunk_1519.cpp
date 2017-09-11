
        if (server.cluster->state != REDIS_CLUSTER_OK) {
            flagTransaction(c);
            clusterRedirectClient(c,NULL,0,REDIS_CLUSTER_REDIR_DOWN_STATE);
            return REDIS_OK;
        } else {
            int error_code;
            clusterNode *n = getNodeByQuery(c,c->cmd,c->argv,c->argc,&hashslot,&error_code);
            if (n == NULL || n != server.cluster->myself) {
                flagTransaction(c);
                clusterRedirectClient(c,n,hashslot,error_code);
                return REDIS_OK;
            }
        }
