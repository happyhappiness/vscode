int main(int argc, char **argv) {
    initServerConfig();
    if (argc == 2) {
        resetServerSaveParams();
        loadServerConfig(argv[1]);
    } else if (argc > 2) {
        fprintf(stderr,"Usage: ./redis-server [/path/to/redis.conf]\n");
        exit(1);
    } else {
        redisLog(REDIS_WARNING,"Warning: no config file specified, using the default config. In order to specify a config file use 'redis-server /path/to/redis.conf'");
    }
    initServer();
    if (server.daemonize) daemonize();
    redisLog(REDIS_NOTICE,"Server started, Redis version " REDIS_VERSION);
#ifdef __linux__
    linuxOvercommitMemoryWarning();
#endif
    if (server.appendonly) {
        if (loadAppendOnlyFile(server.appendfilename) == REDIS_OK)
            redisLog(REDIS_NOTICE,"DB loaded from append only file");
    } else {
        if (rdbLoad(server.dbfilename) == REDIS_OK)
            redisLog(REDIS_NOTICE,"DB loaded from disk");
    }
    if (aeCreateFileEvent(server.el, server.fd, AE_READABLE,
        acceptHandler, NULL, NULL) == AE_ERR) oom("creating file event");
    redisLog(REDIS_NOTICE,"The server is now ready to accept connections on port %d", server.port);
    aeMain(server.el);
    aeDeleteEventLoop(server.el);
    return 0;
}