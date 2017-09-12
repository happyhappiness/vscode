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
