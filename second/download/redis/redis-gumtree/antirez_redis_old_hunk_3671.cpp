        server.stat_starttime = time(NULL);
        addReply(c,shared.ok);
    } else {
        addReplySds(c,sdscatprintf(sdsempty(),
            "-ERR CONFIG subcommand must be one of GET, SET, RESETSTAT\r\n"));
    }
    return;

badarity:
    addReplySds(c,sdscatprintf(sdsempty(),
        "-ERR Wrong number of arguments for CONFIG %s\r\n",
        (char*) c->argv[1]->ptr));
}
