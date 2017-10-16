 #endif
       case 'F': /* --dns-servers */
         /* IP addrs of DNS servers */
         GetStr(&config->dns_servers, nextarg);
         break;
       case 'g': /* --trace */
-        GetStr(&config->trace_dump, nextarg);
-        if(config->tracetype && (config->tracetype != TRACE_BIN))
+        GetStr(&global->trace_dump, nextarg);
+        if(global->tracetype && (global->tracetype != TRACE_BIN))
           warnf(config, "--trace overrides an earlier trace/verbose option\n");
-        config->tracetype = TRACE_BIN;
+        global->tracetype = TRACE_BIN;
+        break;
+      case 'G': /* --npn */
+        config->nonpn = (!toggle)?TRUE:FALSE;
         break;
       case 'h': /* --trace-ascii */
-        GetStr(&config->trace_dump, nextarg);
-        if(config->tracetype && (config->tracetype != TRACE_ASCII))
+        GetStr(&global->trace_dump, nextarg);
+        if(global->tracetype && (global->tracetype != TRACE_ASCII))
           warnf(config,
                 "--trace-ascii overrides an earlier trace/verbose option\n");
-        config->tracetype = TRACE_ASCII;
+        global->tracetype = TRACE_ASCII;
+        break;
+      case 'H': /* --alpn */
+        config->noalpn = (!toggle)?TRUE:FALSE;
         break;
       case 'i': /* --limit-rate */
       {
         /* We support G, M, K too */
         char *unit;
         curl_off_t value = curlx_strtoofft(nextarg, &unit, 0);
