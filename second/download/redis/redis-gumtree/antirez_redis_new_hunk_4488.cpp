 
	
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
