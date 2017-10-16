   }
 
   if(config->trace_stream)
     output = config->trace_stream;
 
   if(!output) {
-    warnf(config, "Failed to create/open output");
+    warnf(operation, "Failed to create/open output");
     return 0;
   }
 
   if(config->tracetype == TRACE_PLAIN) {
     /*
      * This is the trace look that is similar to what libcurl makes on its
