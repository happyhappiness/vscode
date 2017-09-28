                     "rdb_child_pid = %d, aof_child_pid = %d",
                     strerror(errno),
                     (int) server.rdb_child_pid,
                     (int) server.aof_child_pid);
             } else if (pid == server.rdb_child_pid) {
                 backgroundSaveDoneHandler(exitcode,bysignal);
+                if (!bysignal && exitcode == 0) receiveChildInfo();
             } else if (pid == server.aof_child_pid) {
                 backgroundRewriteDoneHandler(exitcode,bysignal);
+                if (!bysignal && exitcode == 0) receiveChildInfo();
             } else {
                 if (!ldbRemoveChild(pid)) {
                     serverLog(LL_WARNING,
                         "Warning, detected child with unmatched pid: %ld",
                         (long)pid);
                 }
             }
             updateDictResizePolicy();
+            closeChildInfoPipe();
         }
     } else {
         /* If there is not a background saving/rewrite in progress check if
          * we have to save/rewrite now */
          for (j = 0; j < server.saveparamslen; j++) {
             struct saveparam *sp = server.saveparams+j;
