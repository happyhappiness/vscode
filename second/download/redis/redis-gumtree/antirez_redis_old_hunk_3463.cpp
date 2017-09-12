
    if (config.idlemode) {
        printf("Creating %d idle connections and waiting forever (Ctrl+C when done)\n", config.numclients);
        prepareForBenchmark("IDLE");
        c = createClient(0); /* will never receive a reply */
        c->obuf = sdsempty();
        createMissingClients(c);
