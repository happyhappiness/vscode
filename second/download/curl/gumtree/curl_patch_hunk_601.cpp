     case 'v':
       if(toggle) {
         /* the '%' thing here will cause the trace get sent to stderr */
         GetStr(&config->trace_dump, (char *)"%");
         if(config->tracetype && (config->tracetype != TRACE_PLAIN))
           warnf(config,
-                "-v/--verbose overrides an earlier trace/verbose option\n");
+                "-v, --verbose overrides an earlier trace/verbose option\n");
         config->tracetype = TRACE_PLAIN;
       }
       else
         /* verbose is disabled here */
         config->tracetype = TRACE_NONE;
       break;
