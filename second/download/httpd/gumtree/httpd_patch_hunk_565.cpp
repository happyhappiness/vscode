 
             if (rc == 0)
                 thefile->bufpos = 0;
         }
 
         return rc;
-    } else {
-        FlushFileBuffers(thefile->filehand);
-        return APR_SUCCESS;
     }
+
+    /* There isn't anything to do if we aren't buffering the output
+     * so just return success.
+     */
+    return APR_SUCCESS; 
 }
 
-static int printf_flush(apr_vformatter_buff_t *vbuff)
+struct apr_file_printf_data {
+    apr_vformatter_buff_t vbuff;
+    apr_file_t *fptr;
+    char *buf;
+};
+
+static int file_printf_flush(apr_vformatter_buff_t *buff)
 {
-    /* I would love to print this stuff out to the file, but I will
-     * get that working later.  :)  For now, just return.
-     */
-    return -1;
+    struct apr_file_printf_data *data = (struct apr_file_printf_data *)buff;
+
+    if (apr_file_write_full(data->fptr, data->buf,
+                            data->vbuff.curpos - data->buf, NULL)) {
+        return -1;
+    }
+
+    data->vbuff.curpos = data->buf;
+    return 0;
 }
 
 APR_DECLARE_NONSTD(int) apr_file_printf(apr_file_t *fptr, 
                                         const char *format, ...)
 {
-    int cc;
+    struct apr_file_printf_data data;
     va_list ap;
-    char *buf;
-    int len;
+    int count;
 
-    buf = malloc(HUGE_STRING_LEN);
-    if (buf == NULL) {
+    data.buf = malloc(HUGE_STRING_LEN);
+    if (data.buf == NULL) {
         return 0;
     }
+    data.vbuff.curpos = data.buf;
+    data.vbuff.endpos = data.buf + HUGE_STRING_LEN;
+    data.fptr = fptr;
     va_start(ap, format);
-    len = apr_vsnprintf(buf, HUGE_STRING_LEN, format, ap);
-    cc = apr_file_puts(buf, fptr);
-    va_end(ap);
-    free(buf);
-    return (cc == APR_SUCCESS) ? len : -1;
-}
+    count = apr_vformatter(file_printf_flush,
+                           (apr_vformatter_buff_t *)&data, format, ap);
+    /* apr_vformatter does not call flush for the last bits */
+    if (count >= 0) file_printf_flush((apr_vformatter_buff_t *)&data);
 
+    va_end(ap);
 
+    free(data.buf);
+    return count;
+}
