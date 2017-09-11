@@ -228,6 +228,6 @@ void latencyCommand(redisClient *c) {
     /* Common error when the user asks for an event we have no latency
      * information about. */
     addReplyErrorFormat(c,
-        "No samples available for event '%s'", c->argv[2]->ptr);
+        "No samples available for event '%s'", (char*) c->argv[2]->ptr);
 }
 