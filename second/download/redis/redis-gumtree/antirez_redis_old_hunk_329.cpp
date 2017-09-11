
#define rdbExitReportCorruptRDB(reason) rdbCheckThenExit(reason, __LINE__);

void rdbCheckThenExit(char *reason, int where) {
    serverLog(LL_WARNING, "Corrupt RDB detected at rdb.c:%d (%s). "
        "Running 'redis-check-rdb %s'",
        where, reason, server.rdb_filename);
    redis_check_rdb(server.rdb_filename);
    exit(1);
}

