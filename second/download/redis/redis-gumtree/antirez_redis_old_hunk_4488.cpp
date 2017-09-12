 
	
  trace_size = backtrace(trace, 100);
  /* overwrite sigaction with caller's address */
  trace[1] = (void *) uc->uc_mcontext.gregs[REG_EIP];

  messages = backtrace_symbols(trace, trace_size);
  
  for (i=1; i<trace_size; ++i)
	redisLog(REDIS_DEBUG,"[bt] %s", messages[i]);

  free(messages);
  exit(0);
