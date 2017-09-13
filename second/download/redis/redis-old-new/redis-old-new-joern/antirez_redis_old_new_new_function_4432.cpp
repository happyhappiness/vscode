static void segvHandler (int sig, siginfo_t *info, void *secret) {

  void *trace[16];
  char **messages = (char **)NULL;
  int i, trace_size = 0;
  ucontext_t *uc = (ucontext_t *)secret;

  /* Do something useful with siginfo_t */
  if (sig == SIGSEGV)
	printf("Got signal %d, faulty address is %p, from %p\n", sig, info->si_addr, 
		   (void *)uc->uc_mcontext.gregs[REG_EIP]);
  else
	printf("Got signal %d\n", sig);
	
  trace_size = backtrace(trace, 16);
  /* overwrite sigaction with caller's address */
  trace[1] = (void *) uc->uc_mcontext.gregs[REG_EIP];

  messages = backtrace_symbols(trace, trace_size);
  /* skip first stack frame (points here) */
  printf("[bt] Execution path:\n");
  for (i=1; i<trace_size; ++i)
	printf("[bt] %s\n", messages[i]);

  exit(0);
}