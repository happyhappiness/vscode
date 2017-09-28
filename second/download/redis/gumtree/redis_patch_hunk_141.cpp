                 if (reply) {
                     if (reply->type == REDIS_REPLY_ERROR) {
                         fprintf(stderr,"%s\n", reply->str);
                         errors++;
                     } else if (eof && reply->type == REDIS_REPLY_STRING &&
                                       reply->len == 20) {
-                        /* Check if this is the reply to our final ECHO 
+                        /* Check if this is the reply to our final ECHO
                          * command. If so everything was received
                          * from the server. */
                         if (memcmp(reply->str,magic,20) == 0) {
                             printf("Last reply received from server.\n");
                             done = 1;
                             replies--;
