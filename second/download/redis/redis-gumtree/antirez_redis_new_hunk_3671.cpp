        server.stat_starttime = time(NULL);
        addReply(c,shared.ok);
    } else {
        addReplyError(c,
            "CONFIG subcommand must be one of GET, SET, RESETSTAT");
    }
    return;

badarity:
    addReplyErrorFormat(c,"Wrong number of arguments for CONFIG %s",
        (char*) c->argv[1]->ptr);
}
