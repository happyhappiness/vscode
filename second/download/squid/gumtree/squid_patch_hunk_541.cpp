 
     c->cutoff.n_denied = c->Icp.result_hist[LOG_UDP_DENIED];
 
     return 1;
 }
 
-log_type &operator++ (log_type &aLogType)
-{
-    int tmp = (int)aLogType;
-    aLogType = (log_type)(++tmp);
-    return aLogType;
-}
-
 void
 clientdbDump(StoreEntry * sentry)
 {
     const char *name;
     ClientInfo *c;
-    log_type l;
     int icp_total = 0;
     int icp_hits = 0;
     int http_total = 0;
     int http_hits = 0;
     storeAppendPrintf(sentry, "Cache Clients:\n");
     hash_first(client_table);
