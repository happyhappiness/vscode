  int i, trace_size = 0;
  long offset=0;
  ucontext_t *uc = (ucontext_t *)secret;
  
  redisLog(REDIS_DEBUG, "Segmentation fault -%d- Redis %s", sig, REDIS_VERSION );
  redisLog(REDIS_DEBUG,"EIP %p",  (void *)uc->uc_mcontext.gregs[REG_EIP]);
  redisLog(REDIS_DEBUG,"EAX %p, EBX %p,  ECX %p, EDX %p", (void *)uc->uc_mcontext.gregs[REG_EAX], (void *)uc->uc_mcontext.gregs[REG_EBX],  (void *)uc->uc_mcontext.gregs[REG_ECX], (void *)uc->uc_mcontext.gregs[REG_EDX]);
 
	
  trace_size = backtrace(trace, 100);
