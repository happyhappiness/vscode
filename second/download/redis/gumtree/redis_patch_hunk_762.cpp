              server.repl_backlog_idx);
 
     /* Compute the amount of bytes we need to discard. */
     skip = offset - server.repl_backlog_off;
     serverLog(LL_DEBUG, "[PSYNC] Skipping: %lld", skip);
 
-    /* Point j to the oldest byte, that is actaully our
+    /* Point j to the oldest byte, that is actually our
      * server.repl_backlog_off byte. */
     j = (server.repl_backlog_idx +
         (server.repl_backlog_size-server.repl_backlog_histlen)) %
         server.repl_backlog_size;
     serverLog(LL_DEBUG, "[PSYNC] Index of first byte: %lld", j);
 
