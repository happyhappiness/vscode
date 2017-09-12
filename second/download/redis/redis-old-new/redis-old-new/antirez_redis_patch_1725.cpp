@@ -661,6 +661,8 @@ void addReplyDouble(redisClient *c, double d);
 void addReplyLongLong(redisClient *c, long long ll);
 void addReplyMultiBulkLen(redisClient *c, long length);
 void *dupClientReplyValue(void *o);
+void getClientsMaxBuffers(unsigned long *longest_output_list,
+                          unsigned long *biggest_input_buffer);
 
 #ifdef __GNUC__
 void addReplyErrorFormat(redisClient *c, const char *fmt, ...)