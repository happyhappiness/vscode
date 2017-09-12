int main(int argc, char **argv) {
    long long start;
    struct timeval tv;

    /* We need to initialize our libraries, and the server configuration. */
    zmalloc_enable_thread_safeness();
    srand(time(NULL)^getpid());
    gettimeofday(&tv,NULL);
    dictSetHashFunctionSeed(tv.tv_sec^tv.tv_usec^getpid());
    initServerConfig();

    if (argc >= 2) {
        int j = 1; /* First option to parse in argv[] */
        sds options = sdsempty();
        char *configfile = NULL;

        /* Handle special options --help and --version */
        if (strcmp(argv[1], "-v") == 0 ||
            strcmp(argv[1], "--version") == 0) version();
        if (strcmp(argv[1], "--help") == 0 ||
            strcmp(argv[1], "-h") == 0) usage();
        if (strcmp(argv[1], "--test-memory") == 0) {
            if (argc == 3) {
                memtest(atoi(argv[2]),10000);
                exit(0);
            } else {
                fprintf(stderr,"Please specify the amount of memory to test in megabytes.\n");
                fprintf(stderr,"Example: ./redis-server --test-memory 4096\n\n");
                exit(1);
            }
        }

        /* First argument is the config file name? */
        if (argv[j][0] != '-' || argv[j][1] != '-')
            configfile = argv[j++];
        /* All the other options are parsed and conceptually appended to the
         * configuration file. For instance --port 6380 will generate the
         * string "port 6380\n" to be parsed after the actual file name
         * is parsed, if any. */
        while(j != argc) {
            if (argv[j][0] == '-' && argv[j][1] == '-') {
                /* Option name */
                if (sdslen(options)) options = sdscat(options,"\n");
                options = sdscat(options,argv[j]+2);
                options = sdscat(options," ");
            } else {
                /* Option argument */
                options = sdscatrepr(options,argv[j],strlen(argv[j]));
                options = sdscat(options," ");
            }
            j++;
        }
        resetServerSaveParams();
        loadServerConfig(configfile,options);
        sdsfree(options);
    } else {
        redisLog(REDIS_WARNING,"Warning: no config file specified, using the default config. In order to specify a config file use 'redis-server /path/to/redis.conf'");
    }
    if (server.daemonize) daemonize();
    initServer();
    if (server.daemonize) createPidFile();
    redisAsciiArt();
    redisLog(REDIS_WARNING,"Server started, Redis version " REDIS_VERSION);
#ifdef __linux__
    linuxOvercommitMemoryWarning();
#endif
    start = ustime();
    if (server.aof_state == REDIS_AOF_ON) {
        if (loadAppendOnlyFile(server.aof_filename) == REDIS_OK)
            redisLog(REDIS_NOTICE,"DB loaded from append only file: %.3f seconds",(float)(ustime()-start)/1000000);
    } else {
        if (rdbLoad(server.rdb_filename) == REDIS_OK) {
            redisLog(REDIS_NOTICE,"DB loaded from disk: %.3f seconds",
                (float)(ustime()-start)/1000000);
        } else if (errno != ENOENT) {
            redisLog(REDIS_WARNING,"Fatal error loading the DB. Exiting.");
            exit(1);
        }
    }
    if (server.ipfd > 0)
        redisLog(REDIS_NOTICE,"The server is now ready to accept connections on port %d", server.port);
    if (server.sofd > 0)
        redisLog(REDIS_NOTICE,"The server is now ready to accept connections at %s", server.unixsocket);
    aeSetBeforeSleepProc(server.el,beforeSleep);
    aeMain(server.el);
    aeDeleteEventLoop(server.el);
    return 0;
}