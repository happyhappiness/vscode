  int i, trace_size = 0;
  long offset=0;
  ucontext_t *uc = (ucontext_t *)secret;
  time_t uptime = time(NULL)-server.stat_starttime;

  redisLog(REDIS_WARNING, "application: redis,  signal: segmentation fault -%d-",REDIS_VERSION, sig);
  redisLog(REDIS_WARNING, "%s", sdscatprintf(sdsempty(),
        "redis_version:%s; "
        "uptime_in_days:%d; "
        "connected_clients:%d; "
        "connected_slaves:%d; "
        "used_memory:%zu; "
        "changes_since_last_save:%lld; "
        "bgsave_in_progress:%d; "
        "last_save_time:%d; "
        "total_connections_received:%lld; "
        "total_commands_processed:%lld; "
        "role:%s;"
        ,REDIS_VERSION,
        uptime,
        listLength(server.clients)-listLength(server.slaves),
        listLength(server.slaves),
        server.usedmemory,
        server.dirty,
        server.bgsaveinprogress,
        server.lastsave,
        server.stat_numconnections,
        server.stat_numcommands,
        server.masterhost == NULL ? "master" : "slave"
    ));

  redisLog(REDIS_WARNING,"EIP %p",  (void *)uc->uc_mcontext.gregs[REG_EIP]);
  redisLog(REDIS_WARNING,"EAX %p, EBX %p,  ECX %p, EDX %p", (void *)uc->uc_mcontext.gregs[REG_EAX], (void *)uc->uc_mcontext.gregs[REG_EBX],  (void *)uc->uc_mcontext.gregs[REG_ECX], (void *)uc->uc_mcontext.gregs[REG_EDX]);
 
	
  trace_size = backtrace(trace, 100);
