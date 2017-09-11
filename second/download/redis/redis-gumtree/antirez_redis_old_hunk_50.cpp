    server.loadmodule_queue = listCreate();
    modules = dictCreate(&modulesDictType,NULL);
    moduleRegisterCoreAPI();
}

/* Load all the modules in the server.loadmodule_queue list, which is
