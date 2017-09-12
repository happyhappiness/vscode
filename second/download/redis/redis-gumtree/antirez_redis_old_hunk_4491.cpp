    }
}

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

void setupSigAction(){
  struct sigaction act;
  sigemptyset (&act.sa_mask);
  /* When the SA_SIGINFO flag is set in sa_flags then sa_sigaction  is used. Otherwise, sa_handler is used */
  act.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND | SA_SIGINFO;
  act.sa_sigaction = segvHandler;
  sigaction (SIGSEGV, &act, NULL);
}

int main(int argc, char **argv) {
	setupSigAction();
#ifdef __linux__
    linuxOvercommitMemoryWarning();
#endif

    initServerConfig();
    if (argc == 2) {
        ResetServerSaveParams();
