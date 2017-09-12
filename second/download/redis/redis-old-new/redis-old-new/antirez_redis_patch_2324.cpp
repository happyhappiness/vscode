@@ -378,7 +378,7 @@ static void getSetCommand(redisClient *c);
 static void ttlCommand(redisClient *c);
 static void slaveofCommand(redisClient *c);
 static void debugCommand(redisClient *c);
-
+static void setupSigSegvAction();
 /*================================= Globals ================================= */
 
 /* Global vars */
@@ -898,6 +898,7 @@ static void initServer() {
 
     signal(SIGHUP, SIG_IGN);
     signal(SIGPIPE, SIG_IGN);
+    setupSigSegvAction();
 
     server.clients = listCreate();
     server.slaves = listCreate();
@@ -4080,6 +4081,39 @@ static void debugCommand(redisClient *c) {
     }
 }
 
+static void segvHandler (int sig, siginfo_t *info, void *secret) {
+
+  void *trace[100];
+  char **messages = (char **)NULL;
+  int i, trace_size = 0;
+  ucontext_t *uc = (ucontext_t *)secret;
+  
+  redisLog(REDIS_DEBUG, "Segmentation fault -%d- Redis %s", sig, REDIS_VERSION );
+  redisLog(REDIS_DEBUG,"EIP %p",  (void *)uc->uc_mcontext.gregs[REG_EIP]);
+  redisLog(REDIS_DEBUG,"EAX %p, EBX %p,  ECX %p, EDX %p", (void *)uc->uc_mcontext.gregs[REG_EAX], (void *)uc->uc_mcontext.gregs[REG_EBX],  (void *)uc->uc_mcontext.gregs[REG_ECX], (void *)uc->uc_mcontext.gregs[REG_EDX]);
+ 
+	
+  trace_size = backtrace(trace, 100);
+  /* overwrite sigaction with caller's address */
+  trace[1] = (void *) uc->uc_mcontext.gregs[REG_EIP];
+
+  messages = backtrace_symbols(trace, trace_size);
+  
+  for (i=1; i<trace_size; ++i)
+	redisLog(REDIS_DEBUG,"[bt] %s", messages[i]);
+
+  free(messages);
+  exit(0);
+}
+
+void setupSigSegvAction(){
+  struct sigaction act;
+  sigemptyset (&act.sa_mask);
+  /* When the SA_SIGINFO flag is set in sa_flags then sa_sigaction  is used. Otherwise, sa_handler is used */
+  act.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND | SA_SIGINFO;
+  act.sa_sigaction = segvHandler;
+  sigaction (SIGSEGV, &act, NULL);
+}
 /* =================================== Main! ================================ */
 
 #ifdef __linux__
@@ -4128,48 +4162,11 @@ static void daemonize(void) {
     }
 }
 
-static void segvHandler (int sig, siginfo_t *info, void *secret) {
-
-  void *trace[16];
-  char **messages = (char **)NULL;
-  int i, trace_size = 0;
-  ucontext_t *uc = (ucontext_t *)secret;
-
-  /* Do something useful with siginfo_t */
-  if (sig == SIGSEGV)
-	printf("Got signal %d, faulty address is %p, from %p\n", sig, info->si_addr, 
-		   (void *)uc->uc_mcontext.gregs[REG_EIP]);
-  else
-	printf("Got signal %d\n", sig);
-	
-  trace_size = backtrace(trace, 16);
-  /* overwrite sigaction with caller's address */
-  trace[1] = (void *) uc->uc_mcontext.gregs[REG_EIP];
-
-  messages = backtrace_symbols(trace, trace_size);
-  /* skip first stack frame (points here) */
-  printf("[bt] Execution path:\n");
-  for (i=1; i<trace_size; ++i)
-	printf("[bt] %s\n", messages[i]);
-
-  exit(0);
-}
-
-void setupSigAction(){
-  struct sigaction act;
-  sigemptyset (&act.sa_mask);
-  /* When the SA_SIGINFO flag is set in sa_flags then sa_sigaction  is used. Otherwise, sa_handler is used */
-  act.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND | SA_SIGINFO;
-  act.sa_sigaction = segvHandler;
-  sigaction (SIGSEGV, &act, NULL);
-}
-
 int main(int argc, char **argv) {
-	setupSigAction();
 #ifdef __linux__
     linuxOvercommitMemoryWarning();
 #endif
-
+    
     initServerConfig();
     if (argc == 2) {
         ResetServerSaveParams();