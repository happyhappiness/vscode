     long long milliseconds = 0; /* initialized to avoid any harmness warning */
 
     if (expire) {
         if (getLongLongFromObjectOrReply(c, expire, &milliseconds, NULL) != REDIS_OK)
             return;
         if (milliseconds <= 0) {
-            addReplyError(c,"invalid expire time in SETEX");
+            addReplyErrorFormat(c,"invalid expire time in %s",c->cmd->name);
             return;
         }
         if (unit == UNIT_SECONDS) milliseconds *= 1000;
     }
 
     if ((flags & REDIS_SET_NX && lookupKeyWrite(c->db,key) != NULL) ||
