        server.stat_expiredkeys = 0;
        server.stat_rejected_conn = 0;
        server.stat_fork_time = 0;
        server.aof_delayed_fsync = 0;
        resetCommandTableStats();
        addReply(c,shared.ok);
    } else {
        addReplyError(c,
            "CONFIG subcommand must be one of GET, SET, RESETSTAT");
    }
    return;

badarity:
    addReplyErrorFormat(c,"Wrong number of arguments for CONFIG %s",
        (char*) c->argv[1]->ptr);
