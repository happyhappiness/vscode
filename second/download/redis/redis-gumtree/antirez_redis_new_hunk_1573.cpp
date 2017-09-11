
void rdbCheckThenExit(char *reason, int where) {
    redisLog(REDIS_WARNING, "Corrupt RDB detected at rdb.c:%d (%s). "
        "Running 'redis-check-rdb %s'",
        where, reason, server.rdb_filename);
    redis_check_rdb(server.rdb_filename);
    exit(1);
