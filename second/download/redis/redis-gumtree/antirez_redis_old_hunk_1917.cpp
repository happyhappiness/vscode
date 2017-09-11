    {
        server.active_expire_enabled = atoi(c->argv[2]->ptr);
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"cmdkeys") && c->argc >= 3) {
        struct redisCommand *cmd = lookupCommand(c->argv[2]->ptr);
        int *keys, numkeys, j;

        if (!cmd) {
            addReplyError(c,"Invalid command specified");
            return;
        } else if ((cmd->arity > 0 && cmd->arity != c->argc-2) ||
                   ((c->argc-2) < -cmd->arity))
        {
            addReplyError(c,"Invalid number of arguments specified for command");
            return;
        }

        keys = getKeysFromCommand(cmd,c->argv+2,c->argc-2,&numkeys);
        addReplyMultiBulkLen(c,numkeys);
        for (j = 0; j < numkeys; j++) addReplyBulk(c,c->argv[keys[j]+2]);
        getKeysFreeResult(keys);
    } else if (!strcasecmp(c->argv[1]->ptr,"error") && c->argc == 3) {
        sds errstr = sdsnewlen("-",1);

