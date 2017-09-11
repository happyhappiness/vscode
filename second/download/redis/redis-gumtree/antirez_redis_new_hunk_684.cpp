#define RDB_LOAD_NONE   0
#define RDB_LOAD_ENC    (1<<0)
#define RDB_LOAD_PLAIN  (1<<1)
#define RDB_LOAD_SDS    (1<<2)

#define rdbExitReportCorruptRDB(reason) rdbCheckThenExit(reason, __LINE__);

