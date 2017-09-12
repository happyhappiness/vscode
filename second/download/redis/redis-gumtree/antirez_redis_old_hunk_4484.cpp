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
