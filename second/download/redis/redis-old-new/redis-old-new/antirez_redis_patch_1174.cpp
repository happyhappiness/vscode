@@ -1206,7 +1206,11 @@ static void findBigKeys(void) {
             fprintf(stderr, "RANDOMKEY error: %s\n",
                 reply1->str);
             exit(1);
+        } else if (reply1->type == REDIS_REPLY_NIL) {
+            fprintf(stderr, "It looks like the database is empty!\n");
+            exit(1);
         }
+
         /* Get the key type */
         reply2 = redisCommand(context,"TYPE %s",reply1->str);
         assert(reply2 && reply2->type == REDIS_REPLY_STATUS);