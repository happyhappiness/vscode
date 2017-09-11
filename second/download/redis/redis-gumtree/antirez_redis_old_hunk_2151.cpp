void sentinelIsRunning(void) {
    redisLog(REDIS_WARNING,"Sentinel runid is %s", server.runid);

    if (server.configfile == NULL || access(server.configfile,W_OK) == -1) {
        redisLog(REDIS_WARNING,"Sentinel started without a config file, or config file not writable. Exiting...");
        exit(1);
    }
}
