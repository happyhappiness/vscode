         /* Hook into pending lookup */
         state->queue = oldstate->queue;
         oldstate->queue = state;
     } else {
         /* No pending lookup found. Sumbit to helper */
 
-        /* Check for queue overload */
-
-        if (def->theHelper->stats.queue_size >= (int)def->theHelper->childs.n_running) {
-            debugs(82, 7, HERE << "'" << def->name << "' queue is too long");
-            assert(inBackground); // or the caller should have checked
-            cbdataFree(state);
-            return;
-        }
-
-        /* Send it off to the helper */
         MemBuf buf;
         buf.init();
-
-        buf.Printf("%s\n", key);
-
+        buf.appendf("%s\n", key);
         debugs(82, 4, "externalAclLookup: looking up for '" << key << "' in '" << def->name << "'.");
 
-        helperSubmit(def->theHelper, buf.buf, externalAclHandleReply, state);
+        if (!def->theHelper->trySubmit(buf.buf, externalAclHandleReply, state)) {
+            debugs(82, 7, HERE << "'" << def->name << "' submit to helper failed");
+            assert(inBackground); // or the caller should have checked
+            delete state;
+            return;
+        }
 
         dlinkAdd(state, &state->list, &def->queue);
 
         buf.clean();
     }
 
