        sds key = c->argv[2]->ptr;

        addReplyLongLong(c,keyHashSlot(key,sdslen(key)));
    } else {
        addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
    }
