        aeMain(config.el);
        endBenchmark();

        prepareForBenchmark("SET");
        c = createClient();
        if (!c) exit(1);
