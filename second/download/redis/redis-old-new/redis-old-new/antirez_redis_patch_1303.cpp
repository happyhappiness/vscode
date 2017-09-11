@@ -1742,10 +1742,52 @@ int prepareForShutdown(int flags) {
 
 /*================================== Commands =============================== */
 
+/* Return 0 if strings are the same, 1 if they are not.
+ * The comparison is performed in a way that prevents an attacker to obtain
+ * information about the nature of the strings just monitoring the execution
+ * time of the function.
+ *
+ * Note that limiting the comparison length to strings up to 512 bytes we
+ * can avoid leaking any information about the password length and any
+ * possible branch misprediction related leak.
+ */
+int time_independent_strcmp(char *a, char *b) {
+    char bufa[REDIS_AUTHPASS_MAX_LEN], bufb[REDIS_AUTHPASS_MAX_LEN];
+    /* The above two strlen perform len(a) + len(b) operations where either
+     * a or b are fixed (our password) length, and the difference is only
+     * relative to the length of the user provided string, so no information
+     * leak is possible in the following two lines of code. */
+    int alen = strlen(a);
+    int blen = strlen(b);
+    int j;
+    int diff = 0;
+
+    /* We can't compare strings longer than our static buffers.
+     * Note that this will never pass the first test in practical circumstances
+     * so there is no info leak. */
+    if (alen > sizeof(bufa) || blen > sizeof(bufb)) return 1;
+
+    memset(bufa,0,sizeof(bufa));        /* Constant time. */
+    memset(bufb,0,sizeof(bufb));        /* Constant time. */
+    /* Again the time of the following two copies is proportional to
+     * len(a) + len(b) so no info is leaked. */
+    memcpy(bufa,a,alen);
+    memcpy(bufb,b,blen);
+
+    /* Always compare all the chars in the two buffers without
+     * conditional expressions. */
+    for (j = 0; j < sizeof(bufa); j++) {
+        diff |= (bufa[j] ^ bufb[j]);
+    }
+    /* Length must be equal as well. */
+    diff |= alen ^ blen;
+    return diff; /* If zero strings are the same. */
+}
+
 void authCommand(redisClient *c) {
     if (!server.requirepass) {
         addReplyError(c,"Client sent AUTH, but no password is set");
-    } else if (!strcmp(c->argv[1]->ptr, server.requirepass)) {
+    } else if (!time_independent_strcmp(c->argv[1]->ptr, server.requirepass)) {
       c->authenticated = 1;
       addReply(c,shared.ok);
     } else {