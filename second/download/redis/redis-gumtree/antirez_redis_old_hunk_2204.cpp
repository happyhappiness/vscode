            sentinelFlushConfig();
            addReply(c,shared.ok);
        }
    } else {
        addReplyErrorFormat(c,"Unknown sentinel subcommand '%s'",
                               (char*)c->argv[1]->ptr);
