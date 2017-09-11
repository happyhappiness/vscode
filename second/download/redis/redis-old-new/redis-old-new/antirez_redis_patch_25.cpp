@@ -2024,8 +2024,13 @@ static void getKeyTypes(redisReply *keys, int *types) {
                 keys->element[i]->str, context->err, context->errstr);
             exit(1);
         } else if(reply->type != REDIS_REPLY_STATUS) {
-            fprintf(stderr, "Invalid reply type (%d) for TYPE on key '%s'!\n",
-                reply->type, keys->element[i]->str);
+            if(reply->type == REDIS_REPLY_ERROR) {
+                fprintf(stderr, "TYPE returned an error: %s\n", reply->str);
+            } else {
+                fprintf(stderr,
+                    "Invalid reply type (%d) for TYPE on key '%s'!\n",
+                    reply->type, keys->element[i]->str);
+            }
             exit(1);
         }
 