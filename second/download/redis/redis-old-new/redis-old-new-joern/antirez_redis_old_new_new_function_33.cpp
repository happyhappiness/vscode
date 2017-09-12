void moduleInitModulesSystem(void) {
    moduleUnblockedClients = listCreate();

    server.loadmodule_queue = listCreate();
    modules = dictCreate(&modulesDictType,NULL);
    moduleRegisterCoreAPI();
    if (pipe(server.module_blocked_pipe) == -1) {
        serverLog(LL_WARNING,
            "Can't create the pipe for module blocking commands: %s",
            strerror(errno));
        exit(1);
    }
    /* Make the pipe non blocking. This is just a best effort aware mechanism
     * and we do not want to block not in the read nor in the write half. */
    anetNonBlock(NULL,server.module_blocked_pipe[0]);
    anetNonBlock(NULL,server.module_blocked_pipe[1]);
}