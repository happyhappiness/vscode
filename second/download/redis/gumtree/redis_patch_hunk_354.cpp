             }
         } else {
             sentinelFlushConfig();
             sentinelEvent(REDIS_WARNING,"+monitor",ri,"%@ quorum %d",ri->quorum);
             addReply(c,shared.ok);
         }
+    } else if (!strcasecmp(c->argv[1]->ptr,"flushconfig")) {
+        sentinelFlushConfig();
+        addReply(c,shared.ok);
+        return;
     } else if (!strcasecmp(c->argv[1]->ptr,"remove")) {
         /* SENTINEL REMOVE <name> */
         sentinelRedisInstance *ri;
 
         if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2]))
             == NULL) return;
         sentinelEvent(REDIS_WARNING,"-monitor",ri,"%@");
         dictDelete(sentinel.masters,c->argv[2]->ptr);
         sentinelFlushConfig();
         addReply(c,shared.ok);
+    } else if (!strcasecmp(c->argv[1]->ptr,"ckquorum")) {
+        /* SENTINEL CKQUORUM <name> */
+        sentinelRedisInstance *ri;
+        int usable;
+
+        if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2]))
+            == NULL) return;
+        int result = sentinelIsQuorumReachable(ri,&usable);
+        if (result == SENTINEL_ISQR_OK) {
+            addReplySds(c, sdscatfmt(sdsempty(),
+                "+OK %i usable Sentinels. Quorum and failover authorization "
+                "can be reached\r\n",usable));
+        } else {
+            sds e = sdscatfmt(sdsempty(),
+                "-NOQUORUM %i usable Sentinels. ",usable);
+            if (result & SENTINEL_ISQR_NOQUORUM)
+                e = sdscat(e,"Not enough available Sentinels to reach the"
+                             " specified quorum for this master");
+            if (result & SENTINEL_ISQR_NOAUTH) {
+                if (result & SENTINEL_ISQR_NOQUORUM) e = sdscat(e,". ");
+                e = sdscat(e, "Not enough available Sentinels to reach the"
+                              " majority and authorize a failover");
+            }
+            e = sdscat(e,"\r\n");
+            addReplySds(c,e);
+        }
     } else if (!strcasecmp(c->argv[1]->ptr,"set")) {
         if (c->argc < 3 || c->argc % 2 == 0) goto numargserr;
         sentinelSetCommand(c);
     } else {
         addReplyErrorFormat(c,"Unknown sentinel subcommand '%s'",
                                (char*)c->argv[1]->ptr);
