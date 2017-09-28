         if (c->argc != 2) goto badarity;
         if (server.configfile == NULL) {
             addReplyError(c,"The server is running without a config file");
             return;
         }
         if (rewriteConfig(server.configfile) == -1) {
-            redisLog(REDIS_WARNING,"CONFIG REWRITE failed: %s", strerror(errno));
+            serverLog(LL_WARNING,"CONFIG REWRITE failed: %s", strerror(errno));
             addReplyErrorFormat(c,"Rewriting config file: %s", strerror(errno));
         } else {
-            redisLog(REDIS_WARNING,"CONFIG REWRITE executed with success.");
+            serverLog(LL_WARNING,"CONFIG REWRITE executed with success.");
             addReply(c,shared.ok);
         }
     } else {
         addReplyError(c,
             "CONFIG subcommand must be one of GET, SET, RESETSTAT, REWRITE");
     }
