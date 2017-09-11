@@ -326,6 +326,7 @@ void debugCommand(redisClient *c) {
 
         if (getLongFromObjectOrReply(c, c->argv[2], &keys, NULL) != REDIS_OK)
             return;
+        dictExpand(c->db->dict,keys);
         for (j = 0; j < keys; j++) {
             snprintf(buf,sizeof(buf),"key:%lu",j);
             key = createStringObject(buf,strlen(buf));