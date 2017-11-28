     if (Config.maxRequestBufferSize <= Config.maxRequestHeaderSize) {
         fatalf("Client request buffer of %u bytes cannot hold a request with %u bytes of headers." \
                " Change client_request_buffer_max or request_header_max_size limits.",
                (uint32_t)Config.maxRequestBufferSize, (uint32_t)Config.maxRequestHeaderSize);
     }
 
+    /*
+     * Disable client side request pipelining if client_persistent_connections OFF.
+     * Waste of resources queueing any pipelined requests when the first will close the connection.
+     */
+    if (Config.pipeline_max_prefetch > 0 && !Config.onoff.client_pconns) {
+        debugs(3, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: pipeline_prefetch " << Config.pipeline_max_prefetch <<
+               " requires client_persistent_connections ON. Forced pipeline_prefetch 0.");
+        Config.pipeline_max_prefetch = 0;
+    }
+
 #if USE_AUTH
     /*
      * disable client side request pipelining. There is a race with
      * Negotiate and NTLM when the client sends a second request on an
      * connection before the authenticate challenge is sent. With
      * pipelining OFF, the client may fail to authenticate, but squid's
      * state will be preserved.
      */
-    if (Config.onoff.pipeline_prefetch) {
+    if (Config.pipeline_max_prefetch > 0) {
         Auth::Config *nego = Auth::Config::Find("Negotiate");
         Auth::Config *ntlm = Auth::Config::Find("NTLM");
         if ((nego && nego->active()) || (ntlm && ntlm->active())) {
-            debugs(3, DBG_IMPORTANT, "WARNING: pipeline_prefetch breaks NTLM and Negotiate authentication. Forced OFF.");
-            Config.onoff.pipeline_prefetch = 0;
+            debugs(3, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: pipeline_prefetch breaks NTLM and Negotiate authentication. Forced pipeline_prefetch 0.");
+            Config.pipeline_max_prefetch = 0;
         }
     }
 #endif
 }
 
 /** Parse a line containing an obsolete directive.
