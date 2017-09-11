
    listRewind(server.loadmodule_queue,&li);
    while((ln = listNext(&li))) {
        struct loadmodule *loadmod = ln->value;
        if (moduleLoad(loadmod->path,(void **)loadmod->argv,loadmod->argc) == C_ERR) {
            serverLog(LL_WARNING,
                "Can't load module from %s: server aborting",
                loadmod->path);
            exit(1);
        }
    }
