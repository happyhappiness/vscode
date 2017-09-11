@@ -443,6 +443,7 @@ void redisProcessCallbacks(redisAsyncContext *ac) {
             if (((redisReply*)reply)->type == REDIS_REPLY_ERROR) {
                 c->err = REDIS_ERR_OTHER;
                 snprintf(c->errstr,sizeof(c->errstr),"%s",((redisReply*)reply)->str);
+                c->reader->fn->freeObject(reply);
                 __redisAsyncDisconnect(ac);
                 return;
             }