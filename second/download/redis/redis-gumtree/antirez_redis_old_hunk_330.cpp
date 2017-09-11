    int doing;                      /* The state while reading the RDB. */
} rdbstate;

#define RDB_CHECK_DOING_START 0
#define RDB_CHECK_DOING_READ_EXPIRE 1
#define RDB_CHECK_DOING_READ_KEY 2
#define RDB_CHECK_DOING_READ_VALUE 3

/* Called on RDB errors. Provides details about the RDB and the offset
 * we were when the error was detected. */
