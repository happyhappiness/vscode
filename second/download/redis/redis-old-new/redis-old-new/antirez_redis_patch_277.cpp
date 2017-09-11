@@ -1123,6 +1123,7 @@ void addReplyBulkSds(client *c, sds s);
 void addReplyError(client *c, const char *err);
 void addReplyStatus(client *c, const char *status);
 void addReplyDouble(client *c, double d);
+void addReplyHumanLongDouble(client *c, long double d);
 void addReplyLongLong(client *c, long long ll);
 void addReplyMultiBulkLen(client *c, long length);
 void copyClientOutputBuffer(client *dst, client *src);