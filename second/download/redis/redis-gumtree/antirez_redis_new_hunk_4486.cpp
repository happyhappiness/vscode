            "-ERR Syntax error, try DEBUG [SEGFAULT|OBJECT <key>]\r\n"));
    }
}
char *findFuncName(void *pointer, long *offset){
	int i, ret=-1;
	long val, off;
	for(i=0; symsTable[i].pointer!=0; i++){
		val=(long)pointer-symsTable[i].pointer;
		if(val>=0 && (off<0 || val <= off)){
			off=val;
			ret=i;
		}
	}
	if(ret<0)
		*offset=0;
	else
		*offset=off;
	return ret>=0?symsTable[ret].name:"unknown";
}

static void segvHandler (int sig, siginfo_t *info, void *secret) {

  void *trace[100];
  char **messages = (char **)NULL;
  char *tmp;
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
  char pointer[trace_size][11];
    /* overwrite sigaction with caller's address */
  trace[1] = (void *) uc->uc_mcontext.gregs[REG_EIP];
 for (i=1; i<trace_size; ++i)
  	snprintf(pointer[i],11,"[%p]", trace[i]);

  messages = backtrace_symbols(trace, trace_size);
  
  for (i=1; i<trace_size; ++i){
	tmp=strstr(messages[i],pointer[i]);
	if((tmp-2)[0]!=')'){
		char *a=findFuncName(trace[i], &offset);
		redisLog(REDIS_WARNING,"#%d (%s+0x%x) %s", i, a, (unsigned int)offset, tmp);
		}
	else
		redisLog(REDIS_WARNING,"#%d %s", i, messages[i]);
	}

  free(messages);
  exit(0);
}

void setupSigSegvAction(){
  struct sigaction act;
  sigemptyset (&act.sa_mask);
  /* When the SA_SIGINFO flag is set in sa_flags then sa_sigaction  is used. Otherwise, sa_handler is used */
  act.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND | SA_SIGINFO;
  act.sa_sigaction = segvHandler;
  sigaction (SIGSEGV, &act, NULL);
}
/* =================================== Main! ================================ */

#ifdef __linux__
