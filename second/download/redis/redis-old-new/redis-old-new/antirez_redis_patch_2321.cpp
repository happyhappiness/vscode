@@ -4195,10 +4195,36 @@ static void segvHandler (int sig, siginfo_t *info, void *secret) {
   int i, trace_size = 0;
   long offset=0;
   ucontext_t *uc = (ucontext_t *)secret;
-  
-  redisLog(REDIS_DEBUG, "Segmentation fault -%d- Redis %s", sig, REDIS_VERSION );
-  redisLog(REDIS_DEBUG,"EIP %p",  (void *)uc->uc_mcontext.gregs[REG_EIP]);
-  redisLog(REDIS_DEBUG,"EAX %p, EBX %p,  ECX %p, EDX %p", (void *)uc->uc_mcontext.gregs[REG_EAX], (void *)uc->uc_mcontext.gregs[REG_EBX],  (void *)uc->uc_mcontext.gregs[REG_ECX], (void *)uc->uc_mcontext.gregs[REG_EDX]);
+  time_t uptime = time(NULL)-server.stat_starttime;
+
+  redisLog(REDIS_WARNING, "application: redis,  signal: segmentation fault -%d-",REDIS_VERSION, sig);
+  redisLog(REDIS_WARNING, "%s", sdscatprintf(sdsempty(),
+        "redis_version:%s; "
+        "uptime_in_days:%d; "
+        "connected_clients:%d; "
+        "connected_slaves:%d; "
+        "used_memory:%zu; "
+        "changes_since_last_save:%lld; "
+        "bgsave_in_progress:%d; "
+        "last_save_time:%d; "
+        "total_connections_received:%lld; "
+        "total_commands_processed:%lld; "
+        "role:%s;"
+        ,REDIS_VERSION,
+        uptime,
+        listLength(server.clients)-listLength(server.slaves),
+        listLength(server.slaves),
+        server.usedmemory,
+        server.dirty,
+        server.bgsaveinprogress,
+        server.lastsave,
+        server.stat_numconnections,
+        server.stat_numcommands,
+        server.masterhost == NULL ? "master" : "slave"
+    ));
+
+  redisLog(REDIS_WARNING,"EIP %p",  (void *)uc->uc_mcontext.gregs[REG_EIP]);
+  redisLog(REDIS_WARNING,"EAX %p, EBX %p,  ECX %p, EDX %p", (void *)uc->uc_mcontext.gregs[REG_EAX], (void *)uc->uc_mcontext.gregs[REG_EBX],  (void *)uc->uc_mcontext.gregs[REG_ECX], (void *)uc->uc_mcontext.gregs[REG_EDX]);
  
 	
   trace_size = backtrace(trace, 100);
@@ -4214,10 +4240,10 @@ static void segvHandler (int sig, siginfo_t *info, void *secret) {
 	tmp=strstr(messages[i],pointer[i]);
 	if((tmp-2)[0]!=')'){
 		char *a=findFuncName(trace[i], &offset);
-		redisLog(REDIS_DEBUG,"[bt] (%s+%x) %s", a, (unsigned int)offset, tmp);
+		redisLog(REDIS_WARNING,"#%d (%s+0x%x) %s", i, a, (unsigned int)offset, tmp);
 		}
 	else
-		redisLog(REDIS_DEBUG,"[bt] %s", messages[i]);
+		redisLog(REDIS_WARNING,"#%d %s", i, messages[i]);
 	}
 
   free(messages);