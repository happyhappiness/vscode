void moduleLoadFromQueue(void) {
    listIter li;
    listNode *ln;

    listRewind(server.loadmodule_queue,&li);
    while((ln = listNext(&li))) {
        sds modulepath = ln->value;
        if (moduleLoad(modulepath) == C_ERR) {
            serverLog(LL_WARNING,
                "Can't load module from %s: server aborting",
                modulepath);
            exit(1);
        }
    }
}