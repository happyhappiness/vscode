             return;
         }
     } else if (nread == 0) {
         serverLog(LL_VERBOSE, "Client closed connection");
         freeClient(c);
         return;
+    } else if (c->flags & CLIENT_MASTER) {
+        /* Append the query buffer to the pending (not applied) buffer
+         * of the master. We'll use this buffer later in order to have a
+         * copy of the string applied by the last command executed. */
+        c->pending_querybuf = sdscatlen(c->pending_querybuf,
+                                        c->querybuf+qblen,nread);
     }
 
     sdsIncrLen(c->querybuf,nread);
     c->lastinteraction = server.unixtime;
-    if (c->flags & CLIENT_MASTER) c->reploff += nread;
+    if (c->flags & CLIENT_MASTER) c->read_reploff += nread;
     server.stat_net_input_bytes += nread;
     if (sdslen(c->querybuf) > server.client_max_querybuf_len) {
         sds ci = catClientInfoString(sdsempty(),c), bytes = sdsempty();
 
         bytes = sdscatrepr(bytes,c->querybuf,64);
         serverLog(LL_WARNING,"Closing client that reached max query buffer length: %s (qbuf initial bytes: %s)", ci, bytes);
         sdsfree(ci);
         sdsfree(bytes);
         freeClient(c);
         return;
     }
-    processInputBuffer(c);
+
+    /* Time to process the buffer. If the client is a master we need to
+     * compute the difference between the applied offset before and after
+     * processing the buffer, to understand how much of the replication stream
+     * was actually applied to the master state: this quantity, and its
+     * corresponding part of the replication stream, will be propagated to
+     * the sub-slaves and to the replication backlog. */
+    if (!(c->flags & CLIENT_MASTER)) {
+        processInputBuffer(c);
+    } else {
+        size_t prev_offset = c->reploff;
+        processInputBuffer(c);
+        size_t applied = c->reploff - prev_offset;
+        if (applied) {
+            replicationFeedSlavesFromMasterStream(server.slaves,
+                    c->pending_querybuf, applied);
+            sdsrange(c->pending_querybuf,applied,-1);
+        }
+    }
 }
 
 void getClientsMaxBuffers(unsigned long *longest_output_list,
                           unsigned long *biggest_input_buffer) {
     client *c;
     listNode *ln;
