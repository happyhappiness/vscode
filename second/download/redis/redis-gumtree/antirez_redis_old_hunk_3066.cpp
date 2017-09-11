    }

    /* Now lookup the command and check ASAP about trivial error conditions
     * such wrong arity, bad command name and so forth. */
    cmd = lookupCommand(c->argv[0]->ptr);
    if (!cmd) {
        addReplyErrorFormat(c,"unknown command '%s'",
            (char*)c->argv[0]->ptr);
        return REDIS_OK;
    } else if ((cmd->arity > 0 && cmd->arity != c->argc) ||
               (c->argc < -cmd->arity)) {
        addReplyErrorFormat(c,"wrong number of arguments for '%s' command",
            cmd->name);
        return REDIS_OK;
    }

    /* Check if the user is authenticated */
    if (server.requirepass && !c->authenticated && cmd->proc != authCommand) {
        addReplyError(c,"operation not permitted");
        return REDIS_OK;
    }

    /* If cluster is enabled, redirect here */
    if (server.cluster_enabled &&
                !(cmd->getkeys_proc == NULL && cmd->firstkey == 0)) {
        int hashslot;

        if (server.cluster.state != REDIS_CLUSTER_OK) {
            addReplyError(c,"The cluster is down. Check with CLUSTER INFO for more information");
            return REDIS_OK;
        } else {
            int ask;
            clusterNode *n = getNodeByQuery(c,cmd,c->argv,c->argc,&hashslot,&ask);
            if (n == NULL) {
                addReplyError(c,"Multi keys request invalid in cluster");
                return REDIS_OK;
