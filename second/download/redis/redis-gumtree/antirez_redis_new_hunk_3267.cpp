            (unsigned long)sdslen(info)));
        addReplySds(c,info);
        addReply(c,shared.crlf);
    } else if (!strcasecmp(c->argv[1]->ptr,"keyslot") && c->argc == 3) {
        sds key = c->argv[2]->ptr;

        addReplyLongLong(c,keyHashSlot(key,sdslen(key)));
    } else {
        addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
    }
