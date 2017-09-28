        shared.bulkhdr[j] = createObject(REDIS_STRING,
            sdscatprintf(sdsempty(),"$%d\r\n",j));
    }
}

void initServerConfig() {
    getRandomHexChars(server.runid,REDIS_RUN_ID_SIZE);
    server.hz = REDIS_DEFAULT_HZ;
    server.runid[REDIS_RUN_ID_SIZE] = '\0';
    server.arch_bits = (sizeof(long) == 8) ? 64 : 32;
    server.port = REDIS_SERVERPORT;
    server.bindaddr = NULL;
    server.unixsocket = NULL;
    server.unixsocketperm = 0;
    server.ipfd = -1;
    server.sofd = -1;
    server.dbnum = REDIS_DEFAULT_DBNUM;
    server.verbosity = REDIS_NOTICE;
    server.maxidletime = REDIS_MAXIDLETIME;
    server.tcpkeepalive = 0;
    server.active_expire_enabled = 1;
    server.client_max_querybuf_len = REDIS_MAX_QUERYBUF_LEN;
    server.saveparams = NULL;
    server.loading = 0;
    server.logfile = NULL; /* NULL = log on standard output */
    server.syslog_enabled = 0;
    server.syslog_ident = zstrdup("redis");
    server.syslog_facility = LOG_LOCAL0;
    server.daemonize = 0;
    server.aof_state = REDIS_AOF_OFF;
    server.aof_fsync = AOF_FSYNC_EVERYSEC;
    server.aof_no_fsync_on_rewrite = 0;
    server.aof_rewrite_perc = REDIS_AOF_REWRITE_PERC;
    server.aof_rewrite_min_size = REDIS_AOF_REWRITE_MIN_SIZE;
    server.aof_rewrite_base_size = 0;
    server.aof_rewrite_scheduled = 0;
    server.aof_last_fsync = time(NULL);
    server.aof_rewrite_time_last = -1;
    server.aof_rewrite_time_start = -1;
    server.aof_lastbgrewrite_status = REDIS_OK;
    server.aof_delayed_fsync = 0;
    server.aof_fd = -1;
    server.aof_selected_db = -1; /* Make sure the first time will not match */
    server.aof_flush_postponed_start = 0;
    server.aof_rewrite_incremental_fsync = 1;
    server.pidfile = zstrdup("/var/run/redis.pid");
    server.rdb_filename = zstrdup("dump.rdb");
    server.aof_filename = zstrdup("appendonly.aof");
    server.requirepass = NULL;
    server.rdb_compression = 1;
    server.rdb_checksum = 1;
    server.stop_writes_on_bgsave_err = 1;
    server.activerehashing = 1;
    server.maxclients = REDIS_MAX_CLIENTS;
    server.bpop_blocked_clients = 0;
    server.maxmemory = 0;
    server.maxmemory_policy = REDIS_MAXMEMORY_VOLATILE_LRU;
    server.maxmemory_samples = 3;
    server.hash_max_ziplist_entries = REDIS_HASH_MAX_ZIPLIST_ENTRIES;
    server.hash_max_ziplist_value = REDIS_HASH_MAX_ZIPLIST_VALUE;
    server.list_max_ziplist_entries = REDIS_LIST_MAX_ZIPLIST_ENTRIES;
    server.list_max_ziplist_value = REDIS_LIST_MAX_ZIPLIST_VALUE;
    server.set_max_intset_entries = REDIS_SET_MAX_INTSET_ENTRIES;
    server.zset_max_ziplist_entries = REDIS_ZSET_MAX_ZIPLIST_ENTRIES;
    server.zset_max_ziplist_value = REDIS_ZSET_MAX_ZIPLIST_VALUE;
    server.shutdown_asap = 0;
    server.repl_ping_slave_period = REDIS_REPL_PING_SLAVE_PERIOD;
    server.repl_timeout = REDIS_REPL_TIMEOUT;
    server.lua_caller = NULL;
    server.lua_time_limit = REDIS_LUA_TIME_LIMIT;
    server.lua_client = NULL;
    server.lua_timedout = 0;

    updateLRUClock();
    resetServerSaveParams();

    appendServerSaveParams(60*60,1);  /* save after 1 hour and 1 change */
    appendServerSaveParams(300,100);  /* save after 5 minutes and 100 changes */
    appendServerSaveParams(60,10000); /* save after 1 minute and 10000 changes */
    /* Replication related */
    server.masterauth = NULL;
    server.masterhost = NULL;
    server.masterport = 6379;
    server.master = NULL;
    server.repl_state = REDIS_REPL_NONE;
    server.repl_syncio_timeout = REDIS_REPL_SYNCIO_TIMEOUT;
    server.repl_serve_stale_data = 1;
    server.repl_slave_ro = 1;
    server.repl_down_since = 0; /* Never connected, repl is down since EVER. */
    server.repl_disable_tcp_nodelay = 0;
    server.slave_priority = REDIS_DEFAULT_SLAVE_PRIORITY;

    /* Client output buffer limits */
    server.client_obuf_limits[REDIS_CLIENT_LIMIT_CLASS_NORMAL].hard_limit_bytes = 0;
    server.client_obuf_limits[REDIS_CLIENT_LIMIT_CLASS_NORMAL].soft_limit_bytes = 0;
    server.client_obuf_limits[REDIS_CLIENT_LIMIT_CLASS_NORMAL].soft_limit_seconds = 0;
    server.client_obuf_limits[REDIS_CLIENT_LIMIT_CLASS_SLAVE].hard_limit_bytes = 1024*1024*256;
    server.client_obuf_limits[REDIS_CLIENT_LIMIT_CLASS_SLAVE].soft_limit_bytes = 1024*1024*64;
    server.client_obuf_limits[REDIS_CLIENT_LIMIT_CLASS_SLAVE].soft_limit_seconds = 60;
    server.client_obuf_limits[REDIS_CLIENT_LIMIT_CLASS_PUBSUB].hard_limit_bytes = 1024*1024*32;
    server.client_obuf_limits[REDIS_CLIENT_LIMIT_CLASS_PUBSUB].soft_limit_bytes = 1024*1024*8;
    server.client_obuf_limits[REDIS_CLIENT_LIMIT_CLASS_PUBSUB].soft_limit_seconds = 60;

    /* Double constants initialization */
    R_Zero = 0.0;
    R_PosInf = 1.0/R_Zero;
    R_NegInf = -1.0/R_Zero;
    R_Nan = R_Zero/R_Zero;
