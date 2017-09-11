@@ -76,35 +76,35 @@ typedef long long mstime_t; /* millisecond time type. */
 
 /* Static server configuration */
 #define CONFIG_DEFAULT_HZ        10      /* Time interrupt calls/sec. */
-#define REDIS_MIN_HZ            1
-#define REDIS_MAX_HZ            500
-#define REDIS_SERVERPORT        6379    /* TCP port */
-#define REDIS_TCP_BACKLOG       511     /* TCP listen backlog */
-#define REDIS_MAXIDLETIME       0       /* default client timeout: infinite */
+#define CONFIG_MIN_HZ            1
+#define CONFIG_MAX_HZ            500
+#define CONFIG_DEFAULT_SERVER_PORT        6379    /* TCP port */
+#define CONFIG_DEFAULT_TCP_BACKLOG       511     /* TCP listen backlog */
+#define CONFIG_DEFAULT_CLIENT_TIMEOUT       0       /* default client timeout: infinite */
 #define CONFIG_DEFAULT_DBNUM     16
-#define REDIS_CONFIGLINE_MAX    1024
-#define REDIS_DBCRON_DBS_PER_CALL 16
-#define REDIS_MAX_WRITE_PER_EVENT (1024*64)
-#define REDIS_SHARED_SELECT_CMDS 10
-#define REDIS_SHARED_INTEGERS 10000
-#define REDIS_SHARED_BULKHDR_LEN 32
-#define REDIS_MAX_LOGMSG_LEN    1024 /* Default maximum length of syslog messages */
-#define REDIS_AOF_REWRITE_PERC  100
-#define REDIS_AOF_REWRITE_MIN_SIZE (64*1024*1024)
-#define REDIS_AOF_REWRITE_ITEMS_PER_CMD 64
-#define REDIS_SLOWLOG_LOG_SLOWER_THAN 10000
-#define REDIS_SLOWLOG_MAX_LEN 128
+#define CONFIG_MAX_LINE    1024
+#define CRON_DBS_PER_CALL 16
+#define NET_MAX_WRITES_PER_EVENT (1024*64)
+#define PROTO_SHARED_SELECT_CMDS 10
+#define OBJ_SHARED_INTEGERS 10000
+#define OBJ_SHARED_BULKHDR_LEN 32
+#define LOG_MAX_LEN    1024 /* Default maximum length of syslog messages */
+#define AOF_REWRITE_PERC  100
+#define AOF_REWRITE_MIN_SIZE (64*1024*1024)
+#define AOF_REWRITE_ITEMS_PER_CMD 64
+#define CONFIG_DEFAULT_SLOWLOG_LOG_SLOWER_THAN 10000
+#define CONFIG_DEFAULT_SLOWLOG_MAX_LEN 128
 #define CONFIG_DEFAULT_MAX_CLIENTS 10000
-#define REDIS_AUTHPASS_MAX_LEN 512
+#define CONFIG_AUTHPASS_MAX_LEN 512
 #define CONFIG_DEFAULT_SLAVE_PRIORITY 100
-#define REDIS_REPL_TIMEOUT 60
-#define REDIS_REPL_PING_SLAVE_PERIOD 10
-#define REDIS_RUN_ID_SIZE 40
-#define REDIS_EOF_MARK_SIZE 40
+#define CONFIG_DEFAULT_REPL_TIMEOUT 60
+#define CONFIG_DEFAULT_REPL_PING_SLAVE_PERIOD 10
+#define CONFIG_RUN_ID_SIZE 40
+#define RDB_EOF_MARK_SIZE 40
 #define CONFIG_DEFAULT_REPL_BACKLOG_SIZE (1024*1024)    /* 1mb */
 #define CONFIG_DEFAULT_REPL_BACKLOG_TIME_LIMIT (60*60)  /* 1 hour */
-#define REDIS_REPL_BACKLOG_MIN_SIZE (1024*16)          /* 16k */
-#define REDIS_BGSAVE_RETRY_DELAY 5 /* Wait a few secs before trying again. */
+#define CONFIG_REPL_BACKLOG_MIN_SIZE (1024*16)          /* 16k */
+#define CONFIG_BGSAVE_RETRY_DELAY 5 /* Wait a few secs before trying again. */
 #define CONFIG_DEFAULT_PID_FILE "/var/run/redis.pid"
 #define CONFIG_DEFAULT_SYSLOG_IDENT "redis"
 #define CONFIG_DEFAULT_CLUSTER_CONFIG_FILE "nodes.conf"
@@ -131,10 +131,10 @@ typedef long long mstime_t; /* millisecond time type. */
 #define CONFIG_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC 1
 #define CONFIG_DEFAULT_MIN_SLAVES_TO_WRITE 0
 #define CONFIG_DEFAULT_MIN_SLAVES_MAX_LAG 10
-#define REDIS_IP_STR_LEN 46 /* INET6_ADDRSTRLEN is 46, but we need to be sure */
-#define REDIS_PEER_ID_LEN (REDIS_IP_STR_LEN+32) /* Must be enough for ip:port */
-#define REDIS_BINDADDR_MAX 16
-#define REDIS_MIN_RESERVED_FDS 32
+#define NET_IP_STR_LEN 46 /* INET6_ADDRSTRLEN is 46, but we need to be sure */
+#define NET_PEER_ID_LEN (NET_IP_STR_LEN+32) /* Must be enough for ip:port */
+#define CONFIG_BINDADDR_MAX 16
+#define CONFIG_MIN_RESERVED_FDS 32
 #define CONFIG_DEFAULT_LATENCY_MONITOR_THRESHOLD 0
 
 #define ACTIVE_EXPIRE_CYCLE_LOOKUPS_PER_LOOP 20 /* Loopkups per loop. */
@@ -144,44 +144,46 @@ typedef long long mstime_t; /* millisecond time type. */
 #define ACTIVE_EXPIRE_CYCLE_FAST 1
 
 /* Instantaneous metrics tracking. */
-#define REDIS_METRIC_SAMPLES 16     /* Number of samples per metric. */
-#define REDIS_METRIC_COMMAND 0      /* Number of commands executed. */
-#define REDIS_METRIC_NET_INPUT 1    /* Bytes read to network .*/
-#define REDIS_METRIC_NET_OUTPUT 2   /* Bytes written to network. */
-#define REDIS_METRIC_COUNT 3
+#define STATS_METRIC_SAMPLES 16     /* Number of samples per metric. */
+#define STATS_METRIC_COMMAND 0      /* Number of commands executed. */
+#define STATS_METRIC_NET_INPUT 1    /* Bytes read to network .*/
+#define STATS_METRIC_NET_OUTPUT 2   /* Bytes written to network. */
+#define STATS_METRIC_COUNT 3
 
 /* Protocol and I/O related defines */
-#define REDIS_MAX_QUERYBUF_LEN  (1024*1024*1024) /* 1GB max query buffer. */
-#define REDIS_IOBUF_LEN         (1024*16)  /* Generic I/O buffer size */
-#define REDIS_REPLY_CHUNK_BYTES (16*1024) /* 16k output buffer */
-#define REDIS_INLINE_MAX_SIZE   (1024*64) /* Max size of inline reads */
-#define REDIS_MBULK_BIG_ARG     (1024*32)
-#define REDIS_LONGSTR_SIZE      21          /* Bytes needed for long -> str */
-#define REDIS_AOF_AUTOSYNC_BYTES (1024*1024*32) /* fdatasync every 32MB */
-/* When configuring the Redis eventloop, we setup it so that the total number
- * of file descriptors we can handle are server.maxclients + RESERVED_FDS + FDSET_INCR
- * that is our safety margin. */
-#define REDIS_EVENTLOOP_FDSET_INCR (REDIS_MIN_RESERVED_FDS+96)
+#define PROTO_MAX_QUERYBUF_LEN  (1024*1024*1024) /* 1GB max query buffer. */
+#define PROTO_IOBUF_LEN         (1024*16)  /* Generic I/O buffer size */
+#define PROTO_REPLY_CHUNK_BYTES (16*1024) /* 16k output buffer */
+#define PROTO_INLINE_MAX_SIZE   (1024*64) /* Max size of inline reads */
+#define PROTO_MBULK_BIG_ARG     (1024*32)
+#define LONG_STR_SIZE      21          /* Bytes needed for long -> str */
+#define AOF_AUTOSYNC_BYTES (1024*1024*32) /* fdatasync every 32MB */
+
+/* When configuring the server eventloop, we setup it so that the total number
+ * of file descriptors we can handle are server.maxclients + RESERVED_FDS +
+ * a few more to stay safe. Since RESERVED_FDS defaults to 32, we add 96
+ * in order to make sure of not over provisioning more than 128 fds. */
+#define CONFIG_FDSET_INCR (CONFIG_MIN_RESERVED_FDS+96)
 
 /* Hash table parameters */
-#define REDIS_HT_MINFILL        10      /* Minimal hash table fill 10% */
+#define HASHTABLE_MIN_FILL        10      /* Minimal hash table fill 10% */
 
 /* Command flags. Please check the command table defined in the redis.c file
  * for more information about the meaning of every flag. */
-#define REDIS_CMD_WRITE 1                   /* "w" flag */
-#define REDIS_CMD_READONLY 2                /* "r" flag */
-#define REDIS_CMD_DENYOOM 4                 /* "m" flag */
-#define REDIS_CMD_NOT_USED_1 8              /* no longer used flag */
-#define REDIS_CMD_ADMIN 16                  /* "a" flag */
-#define REDIS_CMD_PUBSUB 32                 /* "p" flag */
-#define REDIS_CMD_NOSCRIPT  64              /* "s" flag */
-#define REDIS_CMD_RANDOM 128                /* "R" flag */
-#define REDIS_CMD_SORT_FOR_SCRIPT 256       /* "S" flag */
-#define REDIS_CMD_LOADING 512               /* "l" flag */
-#define REDIS_CMD_STALE 1024                /* "t" flag */
-#define REDIS_CMD_SKIP_MONITOR 2048         /* "M" flag */
-#define REDIS_CMD_ASKING 4096               /* "k" flag */
-#define REDIS_CMD_FAST 8192                 /* "F" flag */
+#define CMD_WRITE 1                   /* "w" flag */
+#define CMD_READONLY 2                /* "r" flag */
+#define CMD_DENYOOM 4                 /* "m" flag */
+#define CMD_NOT_USED_1 8              /* no longer used flag */
+#define CMD_ADMIN 16                  /* "a" flag */
+#define CMD_PUBSUB 32                 /* "p" flag */
+#define CMD_NOSCRIPT  64              /* "s" flag */
+#define CMD_RANDOM 128                /* "R" flag */
+#define CMD_SORT_FOR_SCRIPT 256       /* "S" flag */
+#define CMD_LOADING 512               /* "l" flag */
+#define CMD_STALE 1024                /* "t" flag */
+#define CMD_SKIP_MONITOR 2048         /* "M" flag */
+#define CMD_ASKING 4096               /* "k" flag */
+#define CMD_FAST 8192                 /* "F" flag */
 
 /* Object types */
 #define OBJ_STRING 0
@@ -213,115 +215,113 @@ typedef long long mstime_t; /* millisecond time type. */
  * 10|000000 [32 bit integer] => if it's 10, a full 32 bit len will follow
  * 11|000000 this means: specially encoded object will follow. The six bits
  *           number specify the kind of object that follows.
- *           See the REDIS_RDB_ENC_* defines.
+ *           See the RDB_ENC_* defines.
  *
  * Lengths up to 63 are stored using a single byte, most DB keys, and may
  * values, will fit inside. */
-#define REDIS_RDB_6BITLEN 0
-#define REDIS_RDB_14BITLEN 1
-#define REDIS_RDB_32BITLEN 2
-#define REDIS_RDB_ENCVAL 3
-#define REDIS_RDB_LENERR UINT_MAX
+#define RDB_6BITLEN 0
+#define RDB_14BITLEN 1
+#define RDB_32BITLEN 2
+#define RDB_ENCVAL 3
+#define RDB_LENERR UINT_MAX
 
 /* When a length of a string object stored on disk has the first two bits
  * set, the remaining two bits specify a special encoding for the object
  * accordingly to the following defines: */
-#define REDIS_RDB_ENC_INT8 0        /* 8 bit signed integer */
-#define REDIS_RDB_ENC_INT16 1       /* 16 bit signed integer */
-#define REDIS_RDB_ENC_INT32 2       /* 32 bit signed integer */
-#define REDIS_RDB_ENC_LZF 3         /* string compressed with FASTLZ */
+#define RDB_ENC_INT8 0        /* 8 bit signed integer */
+#define RDB_ENC_INT16 1       /* 16 bit signed integer */
+#define RDB_ENC_INT32 2       /* 32 bit signed integer */
+#define RDB_ENC_LZF 3         /* string compressed with FASTLZ */
 
 /* AOF states */
-#define REDIS_AOF_OFF 0             /* AOF is off */
-#define REDIS_AOF_ON 1              /* AOF is on */
-#define REDIS_AOF_WAIT_REWRITE 2    /* AOF waits rewrite to start appending */
+#define AOF_OFF 0             /* AOF is off */
+#define AOF_ON 1              /* AOF is on */
+#define AOF_WAIT_REWRITE 2    /* AOF waits rewrite to start appending */
 
 /* Client flags */
-#define REDIS_SLAVE (1<<0)   /* This client is a slave server */
-#define REDIS_MASTER (1<<1)  /* This client is a master server */
-#define REDIS_MONITOR (1<<2) /* This client is a slave monitor, see MONITOR */
-#define REDIS_MULTI (1<<3)   /* This client is in a MULTI context */
-#define REDIS_BLOCKED (1<<4) /* The client is waiting in a blocking operation */
-#define REDIS_DIRTY_CAS (1<<5) /* Watched keys modified. EXEC will fail. */
-#define REDIS_CLOSE_AFTER_REPLY (1<<6) /* Close after writing entire reply. */
-#define REDIS_UNBLOCKED (1<<7) /* This client was unblocked and is stored in
+#define CLIENT_SLAVE (1<<0)   /* This client is a slave server */
+#define CLIENT_MASTER (1<<1)  /* This client is a master server */
+#define CLIENT_MONITOR (1<<2) /* This client is a slave monitor, see MONITOR */
+#define CLIENT_MULTI (1<<3)   /* This client is in a MULTI context */
+#define CLIENT_BLOCKED (1<<4) /* The client is waiting in a blocking operation */
+#define CLIENT_DIRTY_CAS (1<<5) /* Watched keys modified. EXEC will fail. */
+#define CLIENT_CLOSE_AFTER_REPLY (1<<6) /* Close after writing entire reply. */
+#define CLIENT_UNBLOCKED (1<<7) /* This client was unblocked and is stored in
                                   server.unblocked_clients */
-#define REDIS_LUA_CLIENT (1<<8) /* This is a non connected client used by Lua */
-#define REDIS_ASKING (1<<9)     /* Client issued the ASKING command */
-#define REDIS_CLOSE_ASAP (1<<10)/* Close this client ASAP */
-#define REDIS_UNIX_SOCKET (1<<11) /* Client connected via Unix domain socket */
-#define REDIS_DIRTY_EXEC (1<<12)  /* EXEC will fail for errors while queueing */
-#define REDIS_MASTER_FORCE_REPLY (1<<13)  /* Queue replies even if is master */
-#define REDIS_FORCE_AOF (1<<14)   /* Force AOF propagation of current cmd. */
-#define REDIS_FORCE_REPL (1<<15)  /* Force replication of current cmd. */
-#define REDIS_PRE_PSYNC (1<<16)   /* Instance don't understand PSYNC. */
-#define REDIS_READONLY (1<<17)    /* Cluster client is in read-only state. */
-#define REDIS_PUBSUB (1<<18)      /* Client is in Pub/Sub mode. */
-#define REDIS_PREVENT_PROP (1<<19)  /* Don't propagate to AOF / Slaves. */
+#define CLIENT_LUA (1<<8) /* This is a non connected client used by Lua */
+#define CLIENT_ASKING (1<<9)     /* Client issued the ASKING command */
+#define CLIENT_CLOSE_ASAP (1<<10)/* Close this client ASAP */
+#define CLIENT_UNIX_SOCKET (1<<11) /* Client connected via Unix domain socket */
+#define CLIENT_DIRTY_EXEC (1<<12)  /* EXEC will fail for errors while queueing */
+#define CLIENT_MASTER_FORCE_REPLY (1<<13)  /* Queue replies even if is master */
+#define CLIENT_FORCE_AOF (1<<14)   /* Force AOF propagation of current cmd. */
+#define CLIENT_FORCE_REPL (1<<15)  /* Force replication of current cmd. */
+#define CLIENT_PRE_PSYNC (1<<16)   /* Instance don't understand PSYNC. */
+#define CLIENT_READONLY (1<<17)    /* Cluster client is in read-only state. */
+#define CLIENT_PUBSUB (1<<18)      /* Client is in Pub/Sub mode. */
+#define CLIENT_PREVENT_PROP (1<<19)  /* Don't propagate to AOF / Slaves. */
 
 /* Client block type (btype field in client structure)
- * if REDIS_BLOCKED flag is set. */
-#define REDIS_BLOCKED_NONE 0    /* Not blocked, no REDIS_BLOCKED flag set. */
-#define REDIS_BLOCKED_LIST 1    /* BLPOP & co. */
-#define REDIS_BLOCKED_WAIT 2    /* WAIT for synchronous replication. */
+ * if CLIENT_BLOCKED flag is set. */
+#define BLOCKED_NONE 0    /* Not blocked, no CLIENT_BLOCKED flag set. */
+#define BLOCKED_LIST 1    /* BLPOP & co. */
+#define BLOCKED_WAIT 2    /* WAIT for synchronous replication. */
 
 /* Client request types */
-#define REDIS_REQ_INLINE 1
-#define REDIS_REQ_MULTIBULK 2
+#define PROTO_REQ_INLINE 1
+#define PROTO_REQ_MULTIBULK 2
 
 /* Client classes for client limits, currently used only for
  * the max-client-output-buffer limit implementation. */
-#define REDIS_CLIENT_TYPE_NORMAL 0 /* Normal req-reply clients + MONITORs */
-#define REDIS_CLIENT_TYPE_SLAVE 1  /* Slaves. */
-#define REDIS_CLIENT_TYPE_PUBSUB 2 /* Clients subscribed to PubSub channels. */
-#define REDIS_CLIENT_TYPE_COUNT 3
-
-/* Slave replication state - from the point of view of the slave. */
-#define REDIS_REPL_NONE 0 /* No active replication */
-#define REDIS_REPL_CONNECT 1 /* Must connect to master */
-#define REDIS_REPL_CONNECTING 2 /* Connecting to master */
-#define REDIS_REPL_RECEIVE_PONG 3 /* Wait for PING reply */
-#define REDIS_REPL_TRANSFER 4 /* Receiving .rdb from master */
-#define REDIS_REPL_CONNECTED 5 /* Connected to master */
-
-/* Slave replication state - from the point of view of the master.
+#define CLIENT_TYPE_NORMAL 0 /* Normal req-reply clients + MONITORs */
+#define CLIENT_TYPE_SLAVE 1  /* Slaves. */
+#define CLIENT_TYPE_PUBSUB 2 /* Clients subscribed to PubSub channels. */
+#define CLIENT_TYPE_COUNT 3
+
+/* Slave replication state. Used in server.repl_state for slaves to remember
+ * what to do next. */
+#define REPL_STATE_NONE 0 /* No active replication */
+#define REPL_STATE_CONNECT 1 /* Must connect to master */
+#define REPL_STATE_CONNECTING 2 /* Connecting to master */
+#define REPL_STATE_RECEIVE_PONG 3 /* Wait for PING reply */
+#define REPL_STATE_TRANSFER 4 /* Receiving .rdb from master */
+#define REPL_STATE_CONNECTED 5 /* Connected to master */
+
+/* State of slaves from the POV of the master. Used in client->replstate.
  * In SEND_BULK and ONLINE state the slave receives new updates
- * in its output queue. In the WAIT_BGSAVE state instead the server is waiting
+ * in its output queue. In the WAIT_BGSAVE states instead the server is waiting
  * to start the next background saving in order to send updates to it. */
-#define REDIS_REPL_WAIT_BGSAVE_START 6 /* We need to produce a new RDB file. */
-#define REDIS_REPL_WAIT_BGSAVE_END 7 /* Waiting RDB file creation to finish. */
-#define REDIS_REPL_SEND_BULK 8 /* Sending RDB file to slave. */
-#define REDIS_REPL_ONLINE 9 /* RDB file transmitted, sending just updates. */
+#define SLAVE_STATE_WAIT_BGSAVE_START 6 /* We need to produce a new RDB file. */
+#define SLAVE_STATE_WAIT_BGSAVE_END 7 /* Waiting RDB file creation to finish. */
+#define SLAVE_STATE_SEND_BULK 8 /* Sending RDB file to slave. */
+#define SLAVE_STATE_ONLINE 9 /* RDB file transmitted, sending just updates. */
 
 /* Synchronous read timeout - slave side */
-#define REDIS_REPL_SYNCIO_TIMEOUT 5
+#define CONFIG_REPL_SYNCIO_TIMEOUT 5
 
 /* List related stuff */
-#define REDIS_HEAD 0
-#define REDIS_TAIL 1
+#define LIST_HEAD 0
+#define LIST_TAIL 1
 
 /* Sort operations */
-#define REDIS_SORT_GET 0
-#define REDIS_SORT_ASC 1
-#define REDIS_SORT_DESC 2
-#define REDIS_SORTKEY_MAX 1024
+#define SORT_OP_GET 0
 
 /* Log levels */
-#define REDIS_DEBUG 0
-#define REDIS_VERBOSE 1
-#define REDIS_NOTICE 2
-#define REDIS_WARNING 3
-#define REDIS_LOG_RAW (1<<10) /* Modifier to log without timestamp */
-#define CONFIG_DEFAULT_VERBOSITY REDIS_NOTICE
+#define LL_DEBUG 0
+#define LL_VERBOSE 1
+#define LL_NOTICE 2
+#define LL_WARNING 3
+#define LL_RAW (1<<10) /* Modifier to log without timestamp */
+#define CONFIG_DEFAULT_VERBOSITY LL_NOTICE
 
 /* Supervision options */
-#define REDIS_SUPERVISED_NONE 0
-#define REDIS_SUPERVISED_AUTODETECT 1
-#define REDIS_SUPERVISED_SYSTEMD 2
-#define REDIS_SUPERVISED_UPSTART 3
+#define SUPERVISED_NONE 0
+#define SUPERVISED_AUTODETECT 1
+#define SUPERVISED_SYSTEMD 2
+#define SUPERVISED_UPSTART 3
 
 /* Anti-warning macro... */
-#define REDIS_NOTUSED(V) ((void) V)
+#define UNUSED(V) ((void) V)
 
 #define ZSKIPLIST_MAXLEVEL 32 /* Should be enough for 2^32 elements */
 #define ZSKIPLIST_P 0.25      /* Skiplist P = 1/4 */
@@ -347,64 +347,64 @@ typedef long long mstime_t; /* millisecond time type. */
 #define CONFIG_DEFAULT_HLL_SPARSE_MAX_BYTES 3000
 
 /* Sets operations codes */
-#define REDIS_OP_UNION 0
-#define REDIS_OP_DIFF 1
-#define REDIS_OP_INTER 2
+#define SET_OP_UNION 0
+#define SET_OP_DIFF 1
+#define SET_OP_INTER 2
 
 /* Redis maxmemory strategies */
-#define REDIS_MAXMEMORY_VOLATILE_LRU 0
-#define REDIS_MAXMEMORY_VOLATILE_TTL 1
-#define REDIS_MAXMEMORY_VOLATILE_RANDOM 2
-#define REDIS_MAXMEMORY_ALLKEYS_LRU 3
-#define REDIS_MAXMEMORY_ALLKEYS_RANDOM 4
-#define REDIS_MAXMEMORY_NO_EVICTION 5
-#define CONFIG_DEFAULT_MAXMEMORY_POLICY REDIS_MAXMEMORY_NO_EVICTION
+#define MAXMEMORY_VOLATILE_LRU 0
+#define MAXMEMORY_VOLATILE_TTL 1
+#define MAXMEMORY_VOLATILE_RANDOM 2
+#define MAXMEMORY_ALLKEYS_LRU 3
+#define MAXMEMORY_ALLKEYS_RANDOM 4
+#define MAXMEMORY_NO_EVICTION 5
+#define CONFIG_DEFAULT_MAXMEMORY_POLICY MAXMEMORY_NO_EVICTION
 
 /* Scripting */
-#define REDIS_LUA_TIME_LIMIT 5000 /* milliseconds */
+#define LUA_SCRIPT_TIME_LIMIT 5000 /* milliseconds */
 
 /* Units */
 #define UNIT_SECONDS 0
 #define UNIT_MILLISECONDS 1
 
 /* SHUTDOWN flags */
-#define REDIS_SHUTDOWN_SAVE 1       /* Force SAVE on SHUTDOWN even if no save
+#define SHUTDOWN_SAVE 1       /* Force SAVE on SHUTDOWN even if no save
                                        points are configured. */
-#define REDIS_SHUTDOWN_NOSAVE 2     /* Don't SAVE on SHUTDOWN. */
+#define SHUTDOWN_NOSAVE 2     /* Don't SAVE on SHUTDOWN. */
 
 /* Command call flags, see call() function */
-#define REDIS_CALL_NONE 0
-#define REDIS_CALL_SLOWLOG 1
-#define REDIS_CALL_STATS 2
-#define REDIS_CALL_PROPAGATE 4
-#define REDIS_CALL_FULL (REDIS_CALL_SLOWLOG | REDIS_CALL_STATS | REDIS_CALL_PROPAGATE)
+#define CMD_CALL_NONE 0
+#define CMD_CALL_SLOWLOG 1
+#define CMD_CALL_STATS 2
+#define CMD_CALL_PROPAGATE 4
+#define CMD_CALL_FULL (CMD_CALL_SLOWLOG | CMD_CALL_STATS | CMD_CALL_PROPAGATE)
 
 /* Command propagation flags, see propagate() function */
-#define REDIS_PROPAGATE_NONE 0
-#define REDIS_PROPAGATE_AOF 1
-#define REDIS_PROPAGATE_REPL 2
+#define PROPAGATE_NONE 0
+#define PROPAGATE_AOF 1
+#define PROPAGATE_REPL 2
 
 /* RDB active child save type. */
-#define REDIS_RDB_CHILD_TYPE_NONE 0
-#define REDIS_RDB_CHILD_TYPE_DISK 1     /* RDB is written to disk. */
-#define REDIS_RDB_CHILD_TYPE_SOCKET 2   /* RDB is written to slave socket. */
+#define RDB_CHILD_TYPE_NONE 0
+#define RDB_CHILD_TYPE_DISK 1     /* RDB is written to disk. */
+#define RDB_CHILD_TYPE_SOCKET 2   /* RDB is written to slave socket. */
 
 /* Keyspace changes notification classes. Every class is associated with a
  * character for configuration purposes. */
-#define REDIS_NOTIFY_KEYSPACE (1<<0)    /* K */
-#define REDIS_NOTIFY_KEYEVENT (1<<1)    /* E */
-#define REDIS_NOTIFY_GENERIC (1<<2)     /* g */
-#define REDIS_NOTIFY_STRING (1<<3)      /* $ */
-#define REDIS_NOTIFY_LIST (1<<4)        /* l */
-#define REDIS_NOTIFY_SET (1<<5)         /* s */
-#define REDIS_NOTIFY_HASH (1<<6)        /* h */
-#define REDIS_NOTIFY_ZSET (1<<7)        /* z */
-#define REDIS_NOTIFY_EXPIRED (1<<8)     /* x */
-#define REDIS_NOTIFY_EVICTED (1<<9)     /* e */
-#define REDIS_NOTIFY_ALL (REDIS_NOTIFY_GENERIC | REDIS_NOTIFY_STRING | REDIS_NOTIFY_LIST | REDIS_NOTIFY_SET | REDIS_NOTIFY_HASH | REDIS_NOTIFY_ZSET | REDIS_NOTIFY_EXPIRED | REDIS_NOTIFY_EVICTED)      /* A */
+#define NOTIFY_KEYSPACE (1<<0)    /* K */
+#define NOTIFY_KEYEVENT (1<<1)    /* E */
+#define NOTIFY_GENERIC (1<<2)     /* g */
+#define NOTIFY_STRING (1<<3)      /* $ */
+#define NOTIFY_LIST (1<<4)        /* l */
+#define NOTIFY_SET (1<<5)         /* s */
+#define NOTIFY_HASH (1<<6)        /* h */
+#define NOTIFY_ZSET (1<<7)        /* z */
+#define NOTIFY_EXPIRED (1<<8)     /* x */
+#define NOTIFY_EVICTED (1<<9)     /* e */
+#define NOTIFY_ALL (NOTIFY_GENERIC | NOTIFY_STRING | NOTIFY_LIST | NOTIFY_SET | NOTIFY_HASH | NOTIFY_ZSET | NOTIFY_EXPIRED | NOTIFY_EVICTED)      /* A */
 
 /* Get the first bind addr or NULL */
-#define REDIS_BIND_ADDR (server.bindaddr_count ? server.bindaddr[0] : NULL)
+#define NET_FIRST_BIND_ADDR (server.bindaddr_count ? server.bindaddr[0] : NULL)
 
 /* Using the following macro you can run code inside serverCron() with the
  * specified period, specified in milliseconds.
@@ -414,7 +414,7 @@ typedef long long mstime_t; /* millisecond time type. */
 /* We can print the stacktrace, so our assert is defined this way: */
 #define serverAssertWithInfo(_c,_o,_e) ((_e)?(void)0 : (_serverAssertWithInfo(_c,_o,#_e,__FILE__,__LINE__),_exit(1)))
 #define serverAssert(_e) ((_e)?(void)0 : (_serverAssert(#_e,__FILE__,__LINE__),_exit(1)))
-#define redisPanic(_e) _redisPanic(#_e,__FILE__,__LINE__),_exit(1)
+#define serverPanic(_e) _serverPanic(#_e,__FILE__,__LINE__),_exit(1)
 
 /*-----------------------------------------------------------------------------
  * Data types
@@ -423,13 +423,13 @@ typedef long long mstime_t; /* millisecond time type. */
 /* A redis object, that is a type able to hold a string / list / set */
 
 /* The actual Redis Object */
-#define REDIS_LRU_BITS 24
-#define REDIS_LRU_CLOCK_MAX ((1<<REDIS_LRU_BITS)-1) /* Max value of obj->lru */
-#define REDIS_LRU_CLOCK_RESOLUTION 1000 /* LRU clock resolution in ms */
+#define LRU_BITS 24
+#define LRU_CLOCK_MAX ((1<<LRU_BITS)-1) /* Max value of obj->lru */
+#define LRU_CLOCK_RESOLUTION 1000 /* LRU clock resolution in ms */
 typedef struct redisObject {
     unsigned type:4;
     unsigned encoding:4;
-    unsigned lru:REDIS_LRU_BITS; /* lru time (relative to server.lruclock) */
+    unsigned lru:LRU_BITS; /* lru time (relative to server.lruclock) */
     int refcount;
     void *ptr;
 } robj;
@@ -438,7 +438,7 @@ typedef struct redisObject {
  * If the current resolution is lower than the frequency we refresh the
  * LRU clock (as it should be in production servers) we return the
  * precomputed value, otherwise we need to resort to a function call. */
-#define LRU_CLOCK() ((1000/server.hz <= REDIS_LRU_CLOCK_RESOLUTION) ? server.lruclock : getLRUClock())
+#define LRU_CLOCK() ((1000/server.hz <= LRU_CLOCK_RESOLUTION) ? server.lruclock : getLRUClock())
 
 /* Macro used to initialize a Redis object allocated on the stack.
  * Note that this macro is taken near the structure definition to make sure
@@ -458,7 +458,7 @@ typedef struct redisObject {
  * greater idle times to the right (ascending order).
  *
  * Empty entries have the key pointer set to NULL. */
-#define REDIS_EVICTION_POOL_SIZE 16
+#define MAXMEMORY_EVICTION_POOL_SIZE 16
 struct evictionPoolEntry {
     unsigned long long idle;    /* Object idle time. */
     sds key;                    /* Key name. */
@@ -499,13 +499,13 @@ typedef struct blockingState {
     mstime_t timeout;       /* Blocking operation timeout. If UNIX current time
                              * is > timeout then the operation timed out. */
 
-    /* REDIS_BLOCK_LIST */
+    /* BLOCKED_LIST */
     dict *keys;             /* The keys we are waiting to terminate a blocking
                              * operation such as BLPOP. Otherwise NULL. */
     robj *target;           /* The key that should receive the element,
                              * for BRPOPLPUSH. */
 
-    /* REDIS_BLOCK_WAIT */
+    /* BLOCKED_WAIT */
     int numreplicas;        /* Number of replicas we are waiting for ACK. */
     long long reploffset;   /* Replication offset to reach. */
 } blockingState;
@@ -549,7 +549,7 @@ typedef struct client {
     time_t ctime;           /* Client creation time */
     time_t lastinteraction; /* time of the last interaction, used for timeout */
     time_t obuf_soft_limit_reached_time;
-    int flags;              /* REDIS_SLAVE | REDIS_MONITOR | REDIS_MULTI ... */
+    int flags;              /* CLIENT_SLAVE | CLIENT_MONITOR | CLIENT_MULTI ... */
     int authenticated;      /* when requirepass is non-NULL */
     int replstate;          /* replication state if this is a slave */
     int repl_put_online_on_ack; /* Install slave write handler on ACK. */
@@ -560,10 +560,10 @@ typedef struct client {
     long long reploff;      /* replication offset if this is our master */
     long long repl_ack_off; /* replication ack offset, if this is a slave */
     long long repl_ack_time;/* replication ack time, if this is a slave */
-    char replrunid[REDIS_RUN_ID_SIZE+1]; /* master run id if this is a master */
+    char replrunid[CONFIG_RUN_ID_SIZE+1]; /* master run id if this is a master */
     int slave_listening_port; /* As configured with: SLAVECONF listening-port */
     multiState mstate;      /* MULTI/EXEC state */
-    int btype;              /* Type of blocking op if REDIS_BLOCKED. */
+    int btype;              /* Type of blocking op if CLIENT_BLOCKED. */
     blockingState bpop;     /* blocking state */
     long long woff;         /* Last write global replication offset. */
     list *watched_keys;     /* Keys WATCHED for MULTI/EXEC CAS */
@@ -573,7 +573,7 @@ typedef struct client {
 
     /* Response buffer */
     int bufpos;
-    char buf[REDIS_REPLY_CHUNK_BYTES];
+    char buf[PROTO_REPLY_CHUNK_BYTES];
 } client;
 
 struct saveparam {
@@ -590,10 +590,10 @@ struct sharedObjectsStruct {
     *busykeyerr, *oomerr, *plus, *messagebulk, *pmessagebulk, *subscribebulk,
     *unsubscribebulk, *psubscribebulk, *punsubscribebulk, *del, *rpop, *lpop,
     *lpush, *emptyscan, *minstring, *maxstring,
-    *select[REDIS_SHARED_SELECT_CMDS],
-    *integers[REDIS_SHARED_INTEGERS],
-    *mbulkhdr[REDIS_SHARED_BULKHDR_LEN], /* "*<value>\r\n" */
-    *bulkhdr[REDIS_SHARED_BULKHDR_LEN];  /* "$<value>\r\n" */
+    *select[PROTO_SHARED_SELECT_CMDS],
+    *integers[OBJ_SHARED_INTEGERS],
+    *mbulkhdr[OBJ_SHARED_BULKHDR_LEN], /* "*<value>\r\n" */
+    *bulkhdr[OBJ_SHARED_BULKHDR_LEN];  /* "$<value>\r\n" */
 };
 
 /* ZSETs use a specialized version of Skiplists */
@@ -624,11 +624,11 @@ typedef struct clientBufferLimitsConfig {
     time_t soft_limit_seconds;
 } clientBufferLimitsConfig;
 
-extern clientBufferLimitsConfig clientBufferLimitsDefaults[REDIS_CLIENT_TYPE_COUNT];
+extern clientBufferLimitsConfig clientBufferLimitsDefaults[CLIENT_TYPE_COUNT];
 
 /* The redisOp structure defines a Redis Operation, that is an instance of
  * a command with an argument vector, database ID, propagation target
- * (REDIS_PROPAGATE_*), and command pointer.
+ * (PROPAGATE_*), and command pointer.
  *
  * Currently only used to additionally propagate more commands to AOF/Replication
  * after the propagation of the executed command. */
@@ -671,26 +671,26 @@ struct redisServer {
     dict *commands;             /* Command table */
     dict *orig_commands;        /* Command table before command renaming. */
     aeEventLoop *el;
-    unsigned lruclock:REDIS_LRU_BITS; /* Clock for LRU eviction */
+    unsigned lruclock:LRU_BITS; /* Clock for LRU eviction */
     int shutdown_asap;          /* SHUTDOWN needed ASAP */
     int activerehashing;        /* Incremental rehash in serverCron() */
     char *requirepass;          /* Pass for AUTH command, or NULL */
     char *pidfile;              /* PID file path */
     int arch_bits;              /* 32 or 64 depending on sizeof(long) */
     int cronloops;              /* Number of times the cron function run */
-    char runid[REDIS_RUN_ID_SIZE+1];  /* ID always different at every exec. */
+    char runid[CONFIG_RUN_ID_SIZE+1];  /* ID always different at every exec. */
     int sentinel_mode;          /* True if this instance is a Sentinel. */
     /* Networking */
     int port;                   /* TCP listening port */
     int tcp_backlog;            /* TCP listen() backlog */
-    char *bindaddr[REDIS_BINDADDR_MAX]; /* Addresses we should bind to */
+    char *bindaddr[CONFIG_BINDADDR_MAX]; /* Addresses we should bind to */
     int bindaddr_count;         /* Number of addresses in server.bindaddr[] */
     char *unixsocket;           /* UNIX socket path */
     mode_t unixsocketperm;      /* UNIX socket permission */
-    int ipfd[REDIS_BINDADDR_MAX]; /* TCP socket file descriptors */
+    int ipfd[CONFIG_BINDADDR_MAX]; /* TCP socket file descriptors */
     int ipfd_count;             /* Used slots in ipfd[] */
     int sofd;                   /* Unix socket file descriptor */
-    int cfd[REDIS_BINDADDR_MAX];/* Cluster bus listening socket */
+    int cfd[CONFIG_BINDADDR_MAX];/* Cluster bus listening socket */
     int cfd_count;              /* Used slots in cfd[] */
     list *clients;              /* List of active clients */
     list *clients_to_close;     /* Clients to close asynchronously */
@@ -737,9 +737,9 @@ struct redisServer {
     struct {
         long long last_sample_time; /* Timestamp of last sample in ms */
         long long last_sample_count;/* Count in last sample */
-        long long samples[REDIS_METRIC_SAMPLES];
+        long long samples[STATS_METRIC_SAMPLES];
         int idx;
-    } inst_metric[REDIS_METRIC_COUNT];
+    } inst_metric[STATS_METRIC_COUNT];
     /* Configuration */
     int verbosity;                  /* Loglevel in redis.conf */
     int maxidletime;                /* Client timeout in seconds */
@@ -748,11 +748,11 @@ struct redisServer {
     size_t client_max_querybuf_len; /* Limit for client query buffer length */
     int dbnum;                      /* Total number of configured DBs */
     int supervised;                 /* 1 if supervised, 0 otherwise. */
-    int supervised_mode;            /* See REDIS_SUPERVISED_* */
+    int supervised_mode;            /* See SUPERVISED_* */
     int daemonize;                  /* True if running as a daemon */
-    clientBufferLimitsConfig client_obuf_limits[REDIS_CLIENT_TYPE_COUNT];
+    clientBufferLimitsConfig client_obuf_limits[CLIENT_TYPE_COUNT];
     /* AOF persistence */
-    int aof_state;                  /* REDIS_AOF_(ON|OFF|WAIT_REWRITE) */
+    int aof_state;                  /* AOF_(ON|OFF|WAIT_REWRITE) */
     int aof_fsync;                  /* Kind of fsync() policy */
     char *aof_filename;             /* Name of the AOF file */
     int aof_no_fsync_on_rewrite;    /* Don't fsync if a rewrite is in prog. */
@@ -851,7 +851,7 @@ struct redisServer {
     time_t repl_down_since; /* Unix time at which link with master went down */
     int repl_disable_tcp_nodelay;   /* Disable TCP_NODELAY after SYNC? */
     int slave_priority;             /* Reported in INFO and used by Sentinel. */
-    char repl_master_runid[REDIS_RUN_ID_SIZE+1];  /* Master run id for PSYNC. */
+    char repl_master_runid[CONFIG_RUN_ID_SIZE+1];  /* Master run id for PSYNC. */
     long long repl_master_initial_offset;         /* Master PSYNC offset. */
     /* Replication script cache. */
     dict *repl_scriptcache_dict;        /* SHA1 all slaves are aware of. */
@@ -892,7 +892,7 @@ struct redisServer {
     dict *pubsub_channels;  /* Map channels to list of subscribed clients */
     list *pubsub_patterns;  /* A list of pubsub_patterns */
     int notify_keyspace_events; /* Events to propagate via Pub/Sub. This is an
-                                   xor of REDIS_NOTIFY... flags. */
+                                   xor of NOTIFY_... flags. */
     /* Cluster */
     int cluster_enabled;      /* Is cluster enabled? */
     mstime_t cluster_node_timeout; /* Cluster node timeout. */
@@ -1583,7 +1583,7 @@ void *realloc(void *ptr, size_t size) __attribute__ ((deprecated));
 /* Debugging stuff */
 void _serverAssertWithInfo(client *c, robj *o, char *estr, char *file, int line);
 void _serverAssert(char *estr, char *file, int line);
-void _redisPanic(char *msg, char *file, int line);
+void _serverPanic(char *msg, char *file, int line);
 void bugReportStart(void);
 void serverLogObjectDebugInfo(robj *o);
 void sigsegvHandler(int sig, siginfo_t *info, void *secret);