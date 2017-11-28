 check_null_access_log(customlog *customlog_definitions)
 {
     return customlog_definitions == NULL;
 }
 
 static void
-dump_logformat(StoreEntry * entry, const char *name, logformat * definitions)
-{
-    accessLogDumpLogFormat(entry, name, definitions);
-}
-
-static void
 dump_access_log(StoreEntry * entry, const char *name, customlog * logs)
 {
     customlog *log;
 
     for (log = logs; log; log = log->next) {
         storeAppendPrintf(entry, "%s ", name);
 
         switch (log->type) {
 
-        case CLF_CUSTOM:
+        case Log::Format::CLF_CUSTOM:
             storeAppendPrintf(entry, "%s %s", log->filename, log->logFormat->name);
             break;
 
-        case CLF_NONE:
+        case Log::Format::CLF_NONE:
             storeAppendPrintf(entry, "none");
             break;
 
-        case CLF_SQUID:
+        case Log::Format::CLF_SQUID:
             storeAppendPrintf(entry, "%s squid", log->filename);
             break;
 
-        case CLF_COMMON:
-            storeAppendPrintf(entry, "%s squid", log->filename);
+        case Log::Format::CLF_COMBINED:
+            storeAppendPrintf(entry, "%s combined", log->filename);
             break;
+
+        case Log::Format::CLF_COMMON:
+            storeAppendPrintf(entry, "%s common", log->filename);
+            break;
+
 #if ICAP_CLIENT
-        case CLF_ICAP_SQUID:
+        case Log::Format::CLF_ICAP_SQUID:
             storeAppendPrintf(entry, "%s icap_squid", log->filename);
             break;
 #endif
-        case CLF_AUTO:
-
-            if (log->aclList)
-                storeAppendPrintf(entry, "%s auto", log->filename);
-            else
-                storeAppendPrintf(entry, "%s", log->filename);
+        case Log::Format::CLF_USERAGENT:
+            storeAppendPrintf(entry, "%s useragent", log->filename);
+            break;
 
+        case Log::Format::CLF_REFERER:
+            storeAppendPrintf(entry, "%s referrer", log->filename);
             break;
 
-        case CLF_UNKNOWN:
+        case Log::Format::CLF_UNKNOWN:
             break;
         }
 
         if (log->aclList)
             dump_acl_list(entry, log->aclList);
 
         storeAppendPrintf(entry, "\n");
     }
 }
 
 static void
-free_logformat(logformat ** definitions)
-{
-    while (*definitions) {
-        logformat *format = *definitions;
-        *definitions = format->next;
-        safe_free(format->name);
-        accessLogFreeLogFormat(&format->format);
-        xfree(format);
-    }
-}
-
-static void
 free_access_log(customlog ** definitions)
 {
     while (*definitions) {
         customlog *log = *definitions;
         *definitions = log->next;
 
         log->logFormat = NULL;
-        log->type = CLF_UNKNOWN;
+        log->type = Log::Format::CLF_UNKNOWN;
 
         if (log->aclList)
             aclDestroyAclList(&log->aclList);
 
         safe_free(log->filename);
 
         xfree(log);
     }
 }
 
+/// parses list of integers form name=N1,N2,N3,...
+static bool
+parseNamedIntList(const char *data, const String &name, Vector<int> &list)
+{
+    if (data && (strncmp(data, name.rawBuf(), name.size()) == 0)) {
+        data += name.size();
+        if (*data == '=') {
+            while (true) {
+                ++data;
+                int value = 0;
+                if (!StringToInt(data, value, &data, 10))
+                    break;
+                list.push_back(value);
+                if (*data == '\0' || *data != ',')
+                    break;
+            }
+        }
+    }
+    return data && *data == '\0';
+}
+
+static void
+parse_CpuAffinityMap(CpuAffinityMap **const cpuAffinityMap)
+{
+#if !HAVE_CPU_AFFINITY
+    debugs(3, DBG_CRITICAL, "FATAL: Squid built with no CPU affinity " <<
+           "support, do not set 'cpu_affinity_map'");
+    self_destruct();
+#endif /* HAVE_CPU_AFFINITY */
+
+    if (!*cpuAffinityMap)
+        *cpuAffinityMap = new CpuAffinityMap;
+
+    const char *const pToken = strtok(NULL, w_space);
+    const char *const cToken = strtok(NULL, w_space);
+    Vector<int> processes, cores;
+    if (!parseNamedIntList(pToken, "process_numbers", processes)) {
+        debugs(3, DBG_CRITICAL, "FATAL: bad 'process_numbers' parameter " <<
+               "in 'cpu_affinity_map'");
+        self_destruct();
+    } else if (!parseNamedIntList(cToken, "cores", cores)) {
+        debugs(3, DBG_CRITICAL, "FATAL: bad 'cores' parameter in " <<
+               "'cpu_affinity_map'");
+        self_destruct();
+    } else if (!(*cpuAffinityMap)->add(processes, cores)) {
+        debugs(3, DBG_CRITICAL, "FATAL: bad 'cpu_affinity_map'; " <<
+               "process_numbers and cores lists differ in length or " <<
+               "contain numbers <= 0");
+        self_destruct();
+    }
+}
+
+static void
+dump_CpuAffinityMap(StoreEntry *const entry, const char *const name, const CpuAffinityMap *const cpuAffinityMap)
+{
+    if (cpuAffinityMap) {
+        storeAppendPrintf(entry, "%s process_numbers=", name);
+        for (size_t i = 0; i < cpuAffinityMap->processes().size(); ++i) {
+            storeAppendPrintf(entry, "%s%i", (i ? "," : ""),
+                              cpuAffinityMap->processes()[i]);
+        }
+        storeAppendPrintf(entry, " cores=");
+        for (size_t i = 0; i < cpuAffinityMap->cores().size(); ++i) {
+            storeAppendPrintf(entry, "%s%i", (i ? "," : ""),
+                              cpuAffinityMap->cores()[i]);
+        }
+        storeAppendPrintf(entry, "\n");
+    }
+}
+
+static void
+free_CpuAffinityMap(CpuAffinityMap **const cpuAffinityMap)
+{
+    delete *cpuAffinityMap;
+    *cpuAffinityMap = NULL;
+}
+
 #if USE_ADAPTATION
 
 static void
 parse_adaptation_service_set_type()
 {
     Adaptation::Config::ParseServiceSet();
