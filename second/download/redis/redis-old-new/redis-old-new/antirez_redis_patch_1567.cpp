@@ -819,6 +819,7 @@ void addReplyMultiBulkLen(redisClient *c, long length);
 void *dupClientReplyValue(void *o);
 void getClientsMaxBuffers(unsigned long *longest_output_list,
                           unsigned long *biggest_input_buffer);
+void rewriteClientCommandVector(redisClient *c, int argc, ...);
 
 #ifdef __GNUC__
 void addReplyErrorFormat(redisClient *c, const char *fmt, ...)