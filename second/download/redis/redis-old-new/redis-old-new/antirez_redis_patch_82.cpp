@@ -1539,6 +1539,7 @@ int slaveTryPartialResynchronization(int fd, int read_reply) {
         serverLog(LL_NOTICE,
             "Master is currently unable to PSYNC "
             "but should be in the future: %s", reply);
+        sdsfree(reply);
         return PSYNC_TRY_LATER;
     }
 