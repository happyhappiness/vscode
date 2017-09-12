
    if (config.idlemode) {
        printf("Creating %d idle connections and waiting forever (Ctrl+C when done)\n", config.numclients);
        prepareForBenchmark("IDLE");
        c = createClient();
        if (!c) exit(1);
        c->obuf = sdsempty();
