        addReplyMultiBulkLen(c,numkeys);
        for (j = 0; j < numkeys; j++) addReplyBulk(c,c->argv[keys[j]+2]);
        getKeysFreeResult(keys);
    } else {
        addReplyErrorFormat(c, "Unknown DEBUG subcommand or wrong number of arguments for '%s'",
            (char*)c->argv[1]->ptr);
