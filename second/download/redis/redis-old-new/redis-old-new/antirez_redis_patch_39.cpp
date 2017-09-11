@@ -1357,6 +1357,7 @@ int rewriteAppendOnlyFileBackground(void) {
             serverLog(LL_WARNING,
                 "Can't rewrite append only file in background: fork: %s",
                 strerror(errno));
+            aofClosePipes();
             return C_ERR;
         }
         serverLog(LL_NOTICE,