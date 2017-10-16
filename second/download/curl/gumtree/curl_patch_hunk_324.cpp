       /* Proxy user:password  */
       GetStr(&config->proxyuserpwd, nextarg);
       cleanarg(nextarg);
       checkpasswd("proxy", &config->proxyuserpwd);
       break;
     case 'v':
-      /* the '%' thing here will cause the trace get sent to stderr */
-      GetStr(&config->trace_dump, (char *)"%");
-      if(config->tracetype && (config->tracetype != TRACE_PLAIN))
-        warnf(config,
-              "-v/--verbose overrides an earlier trace/verbose option\n");
-      config->tracetype = TRACE_PLAIN;
+      if(toggle) {
+        /* the '%' thing here will cause the trace get sent to stderr */
+        GetStr(&config->trace_dump, (char *)"%");
+        if(config->tracetype && (config->tracetype != TRACE_PLAIN))
+          warnf(config,
+                "-v/--verbose overrides an earlier trace/verbose option\n");
+        config->tracetype = TRACE_PLAIN;
+      }
+      else
+        /* verbose is disabled here */
+        config->tracetype = TRACE_NONE;
       break;
     case 'V':
     {
       const char * const *proto;
 
+      if(!toggle)
+        /* --no-version yields no output! */
+        break;
+
       printf(CURL_ID "%s\n", curl_version());
       if (curlinfo->protocols) {
         printf("Protocols: ");
         for (proto=curlinfo->protocols; *proto; ++proto) {
           printf("%s ", *proto);
         }
