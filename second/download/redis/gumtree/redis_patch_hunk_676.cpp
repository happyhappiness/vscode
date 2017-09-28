                 return C_ERR;
             }
             serverLog(LL_WARNING,
                 "There is a child rewriting the AOF. Killing it!");
             kill(server.aof_child_pid,SIGUSR1);
         }
-        /* Append only file: fsync() the AOF and exit */
+        /* Append only file: flush buffers and fsync() the AOF at exit */
         serverLog(LL_NOTICE,"Calling fsync() on the AOF file.");
+        flushAppendOnlyFile(1);
         aof_fsync(server.aof_fd);
     }
 
     /* Create a new RDB file before exiting. */
     if ((server.saveparamslen > 0 && !nosave) || save) {
         serverLog(LL_NOTICE,"Saving the final RDB snapshot before exiting.");
