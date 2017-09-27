  */
 
 #include "ajp.h"
 
 APLOG_USE_MODULE(proxy_ajp);
 
+#define AJP_MSG_DUMP_BYTES_PER_LINE 16
+/* 2 hex digits plus space plus one char per dumped byte */
+/* plus prefix plus separator plus '\0' */
+#define AJP_MSG_DUMP_LINE_LENGTH    (strlen("XX .") + \
+                                     strlen("XXXX    ") + \
+                                     strlen(" - ") + 1)
+
 static char *hex_table = "0123456789ABCDEF";
 
 /**
- * Dump up to the first 1024 bytes on an AJP Message
+ * Dump the given number of bytes on an AJP Message
  *
  * @param pool      pool to allocate from
  * @param msg       AJP Message to dump
  * @param err       error string to display
- * @return          dump message
+ * @param count     the number of bytes to dump
+ * @param buf       buffer pointer for dump message
+ * @return          APR_SUCCESS or error
  */
-char * ajp_msg_dump(apr_pool_t *pool, ajp_msg_t *msg, char *err)
+apr_status_t ajp_msg_dump(apr_pool_t *pool, ajp_msg_t *msg, char *err,
+                          apr_size_t count, char **buf)
 {
     apr_size_t  i, j;
-    char        line[80];
     char        *current;
-    char        *rv, *p;
-    apr_size_t  bl = 8192;
+    apr_size_t  bl, rl;
     apr_byte_t  x;
     apr_size_t  len = msg->len;
+    apr_size_t  line_len;
 
-    /* Display only first 1024 bytes */
-    if (len > 1024)
-        len = 1024;
-    rv = apr_palloc(pool, bl);
-    apr_snprintf(rv, bl,
-                 "ajp_msg_dump(): %s pos=%" APR_SIZE_T_FMT
+    /* Display only first "count" bytes */
+    if (len > count)
+        len = count;
+         /* First the space needed for the first line */
+    bl = strlen(err) + 3 * (strlen(" XXX=") + 20) + 1 +
+         /* Now for the data lines */
+         (len + 15) / 16 * AJP_MSG_DUMP_LINE_LENGTH;
+    *buf = apr_palloc(pool, bl);
+    if (!*buf)
+        return APR_ENOMEM;
+    apr_snprintf(*buf, bl,
+                 "%s pos=%" APR_SIZE_T_FMT
                  " len=%" APR_SIZE_T_FMT " max=%" APR_SIZE_T_FMT "\n",
                  err, msg->pos, msg->len, msg->max_size);
-    bl -= strlen(rv);
-    p = rv + strlen(rv);
-    for (i = 0; i < len; i += 16) {
-        current = line;
-
-        for (j = 0; j < 16; j++) {
+    current = *buf + strlen(*buf);
+    for (i = 0; i < len; i += AJP_MSG_DUMP_BYTES_PER_LINE) {
+        /* Safety check: do we have enough buffer for another line? */
+        rl = bl - (current - *buf);
+        if (AJP_MSG_DUMP_LINE_LENGTH > rl) {
+            *(current - 1) = '\0';
+            return APR_ENOMEM;
+        }
+        apr_snprintf(current, rl, "%.4lx    ", (unsigned long)i);
+        line_len = len - i;
+        if (line_len > AJP_MSG_DUMP_BYTES_PER_LINE) {
+            line_len = AJP_MSG_DUMP_BYTES_PER_LINE;
+        }
+        for (j = 0; j < line_len; j++) {
              x = msg->buf[i + j];
 
             *current++ = hex_table[x >> 4];
             *current++ = hex_table[x & 0x0f];
             *current++ = ' ';
         }
         *current++ = ' ';
         *current++ = '-';
         *current++ = ' ';
-        for (j = 0; j < 16; j++) {
+        for (j = 0; j < line_len; j++) {
             x = msg->buf[i + j];
 
             if (x > 0x20 && x < 0x7F) {
                 *current++ = x;
             }
             else {
                 *current++ = '.';
             }
         }
-
-        *current++ = '\0';
-        apr_snprintf(p, bl,
-                     "ajp_msg_dump(): %.4lx    %s\n",
-                     (unsigned long)i, line);
-        bl -= strlen(rv);
-        p = rv + strlen(rv);
-
+        *current++ = '\n';
     }
+    *(current - 1) = '\0';
 
-    return rv;
+    return APR_SUCCESS;
 }
 
+/**
+ * Log an AJP message
+ *
+ * @param request   The current request
+ * @param msg       AJP Message to dump
+ * @param err       error string to display
+ * @return          APR_SUCCESS or error
+ */
+apr_status_t ajp_msg_log(request_rec *r, ajp_msg_t *msg, char *err)
+{
+    int level;
+    apr_size_t count;
+    char *buf, *next;
+    apr_status_t rc = APR_SUCCESS;
+
+    if (APLOGrtrace7(r)) {
+        level = APLOG_TRACE7;
+        count = 1024;
+        if (APLOGrtrace8(r)) {
+            level = APLOG_TRACE8;
+            count = AJP_MAX_BUFFER_SZ;
+        }
+        rc = ajp_msg_dump(r->pool, msg, err, count, &buf);
+        if (rc == APR_SUCCESS) {
+            while ((next = ap_strchr(buf, '\n'))) {
+                *next = '\0';
+                ap_log_rerror(APLOG_MARK, level, 0, r, "%s", buf);
+                buf = next + 1;
+            }
+            ap_log_rerror(APLOG_MARK, level, 0, r, "%s", buf);
+        }
+    }
+    return rc;
+}
 
 /**
  * Check a new AJP Message by looking at signature and return its size
  *
  * @param msg       AJP Message to check
  * @param len       Pointer to returned len
