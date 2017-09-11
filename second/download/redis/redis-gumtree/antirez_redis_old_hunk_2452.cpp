        addReplyMultiBulkLen(c,numkeys);
        for (j = 0; j < numkeys; j++) addReplyBulk(c,keys[j]);
        zfree(keys);
    } else {
        addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
    }
