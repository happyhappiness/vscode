            (unsigned long)sdslen(info)));
        addReplySds(c,info);
        addReply(c,shared.crlf);
    } else {
        addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
    }
