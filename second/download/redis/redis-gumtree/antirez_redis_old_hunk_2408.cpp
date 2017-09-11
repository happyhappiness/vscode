        server.aof_delayed_fsync = 0;
        resetCommandTableStats();
        addReply(c,shared.ok);
    } else {
        addReplyError(c,
            "CONFIG subcommand must be one of GET, SET, RESETSTAT");
