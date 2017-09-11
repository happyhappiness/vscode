        if (!cmd) {
            addReplyError(c,"Invalid command specified");
            return;
        }
        keys = getKeysFromCommand(cmd,c->argv+2,c->argc-2,&numkeys);
        addReplyMultiBulkLen(c,numkeys);
        for (j = 0; j < numkeys; j++) addReplyBulk(c,c->argv[keys[j]+2]);
