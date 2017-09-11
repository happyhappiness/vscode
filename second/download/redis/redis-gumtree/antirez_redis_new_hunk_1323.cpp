    uint64_t *ok_slaves;

    if (!bysignal && exitcode == 0) {
        serverLog(REDIS_NOTICE,
            "Background RDB transfer terminated with success");
    } else if (!bysignal && exitcode != 0) {
        serverLog(REDIS_WARNING, "Background transfer error");
    } else {
        serverLog(REDIS_WARNING,
            "Background transfer terminated by signal %d", bysignal);
    }
    server.rdb_child_pid = -1;
