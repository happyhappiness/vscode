             default:
                 addReplyError(c,"Unspecified error adding the instance");
                 break;
             }
         } else {
             sentinelFlushConfig();
+            sentinelEvent(REDIS_WARNING,"+monitor",ri,"%@ quorum %d",ri->quorum);
             addReply(c,shared.ok);
         }
     } else if (!strcasecmp(c->argv[1]->ptr,"remove")) {
         /* SENTINEL REMOVE <name> */
         sentinelRedisInstance *ri;
 
         if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2]))
             == NULL) return;
+        sentinelEvent(REDIS_WARNING,"-monitor",ri,"%@");
         dictDelete(sentinel.masters,c->argv[2]->ptr);
         sentinelFlushConfig();
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"set")) {
         if (c->argc < 3 || c->argc % 2 == 0) goto numargserr;
         sentinelSetCommand(c);
