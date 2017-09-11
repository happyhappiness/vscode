        stats = sdscat(stats,buf);

        addReplyBulkSds(c,stats);
    } else {
        addReplyErrorFormat(c, "Unknown DEBUG subcommand or wrong number of arguments for '%s'",
            (char*)c->argv[1]->ptr);
