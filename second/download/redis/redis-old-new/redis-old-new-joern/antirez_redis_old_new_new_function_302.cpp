void rdbCheckThenExit(char *reason, int where) {
     if (!rdbCheckMode) {
        serverLog(LL_WARNING, "Corrupt RDB detected at rdb.c:%d (%s). "
            "Running 'redis-check-rdb %s'",
            where, reason, server.rdb_filename);
        char *argv[2] = {"",server.rdb_filename};
        redis_check_rdb_main(2,argv);
    } else {
        rdbCheckError("Internal error in RDB reading function at rdb.c:%d (%s)",
            where, reason);
    }
    exit(1);
}