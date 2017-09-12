@@ -2772,7 +2772,7 @@ static void sortCommand(redisClient *c) {
 
             if (sop->type == REDIS_SORT_GET) {
                 if (!val || val->type != REDIS_STRING) {
-                    addReply(c,shared.minus1);
+                    addReply(c,shared.nullbulk);
                 } else {
                     addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",
                         sdslen(val->ptr)));