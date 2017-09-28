#include <sys/param.h>

#define RDB_LOAD_NONE   0
#define RDB_LOAD_ENC    (1<<0)
#define RDB_LOAD_PLAIN  (1<<1)

#define rdbExitReportCorruptRDB(reason) rdbCheckThenExit(reason, __LINE__);

void rdbCheckThenExit(char *reason, int where) {
    serverLog(LL_WARNING, "Corrupt RDB detected at rdb.c:%d (%s). "
        "Running 'redis-check-rdb %s'",
        where, reason, server.rdb_filename);
    redis_check_rdb(server.rdb_filename);
    exit(1);
}

static int rdbWriteRaw(rio *rdb, void *p, size_t len) {
    if (rdb && rioWrite(rdb,p,len) == 0)
        return -1;
