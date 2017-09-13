static void segvHandler (int sig, siginfo_t *info, void *secret) {

  void *trace[100];
  char **messages = (char **)NULL;
  char *tmp;
  int i, trace_size = 0;
  long offset=0;
  ucontext_t *uc = (ucontext_t *)secret;
  
  redisLog(REDIS_DEBUG, "Segmentation fault -%d- Redis %s", sig, REDIS_VERSION );
  redisLog(REDIS_DEBUG,"EIP %p",  (void *)uc->uc_mcontext.gregs[REG_EIP]);
  redisLog(REDIS_DEBUG,"EAX %p, EBX %p,  ECX %p, EDX %p", (void *)uc->uc_mcontext.gregs[REG_EAX], (void *)uc->uc_mcontext.gregs[REG_EBX],  (void *)uc->uc_mcontext.gregs[REG_ECX], (void *)uc->uc_mcontext.gregs[REG_EDX]);
 
	
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
		redisLog(REDIS_DEBUG,"[bt] (%s+%x) %s", a, (unsigned int)offset, tmp);
		}
	else
		redisLog(REDIS_DEBUG,"[bt] %s", messages[i]);
	}

  free(messages);
  exit(0);
}