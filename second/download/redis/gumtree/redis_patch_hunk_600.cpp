             return;
         }
         if (sentinelSelectSlave(ri) == NULL) {
             addReplySds(c,sdsnew("-NOGOODSLAVE No suitable slave to promote\r\n"));
             return;
         }
-        redisLog(REDIS_WARNING,"Executing user requested FAILOVER of '%s'",
+        serverLog(LL_WARNING,"Executing user requested FAILOVER of '%s'",
             ri->name);
         sentinelStartFailover(ri);
         ri->flags |= SRI_FORCE_FAILOVER;
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"pending-scripts")) {
         /* SENTINEL PENDING-SCRIPTS */
