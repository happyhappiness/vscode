             default:
                 addReplyError(c,"Unspecified error adding the instance");
                 break;
             }
         } else {
             sentinelFlushConfig();
-            sentinelEvent(REDIS_WARNING,"+monitor",ri,"%@ quorum %d",ri->quorum);
+            sentinelEvent(LL_WARNING,"+monitor",ri,"%@ quorum %d",ri->quorum);
             addReply(c,shared.ok);
         }
     } else if (!strcasecmp(c->argv[1]->ptr,"flushconfig")) {
         if (c->argc != 2) goto numargserr;
         sentinelFlushConfig();
         addReply(c,shared.ok);
