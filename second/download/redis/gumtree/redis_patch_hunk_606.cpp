 /* Our fake PUBLISH command: it is actually useful only to receive hello messages
  * from the other sentinel instances, and publishing to a channel other than
  * SENTINEL_HELLO_CHANNEL is forbidden.
  *
  * Because we have a Sentinel PUBLISH, the code to send hello messages is the same
  * for all the three kind of instances: masters, slaves, sentinels. */
-void sentinelPublishCommand(redisClient *c) {
+void sentinelPublishCommand(client *c) {
     if (strcmp(c->argv[1]->ptr,SENTINEL_HELLO_CHANNEL)) {
         addReplyError(c, "Only HELLO messages are accepted by Sentinel instances.");
         return;
     }
     sentinelProcessHelloMessage(c->argv[2]->ptr,sdslen(c->argv[2]->ptr));
     addReplyLongLong(c,1);
