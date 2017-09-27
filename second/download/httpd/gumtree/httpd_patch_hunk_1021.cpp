     int i;    
 
     for (i = 0; i < len-1; i++) {
         readlen = 1;
         rv = apr_file_read(thefile, str+i, &readlen);
 
-        if (rv != APR_SUCCESS && rv != APR_EOF)
-            return rv;
-
-        if (readlen == 0) {
-            /* If we have bytes, defer APR_EOF to the next call */
-            if (i > 0)
-                rv = APR_SUCCESS;
+        if (readlen != 1) {
+            rv = APR_EOF;
             break;
         }
         
         if (str[i] == '\n') {
             i++; /* don't clobber this char below */
             break;
         }
     }
     str[i] = 0;
+    if (i > 0) {
+        /* we stored chars; don't report EOF or any other errors;
+         * the app will find out about that on the next call
+         */
+        return APR_SUCCESS;
+    }
     return rv;
 }
 
 APR_DECLARE(apr_status_t) apr_file_flush(apr_file_t *thefile)
 {
     if (thefile->buffered) {
-        DWORD written = 0;
+        DWORD numbytes, written = 0;
         apr_status_t rc = 0;
+        char *buffer;
+        apr_size_t bytesleft;
 
         if (thefile->direction == 1 && thefile->bufpos) {
-            if (!WriteFile(thefile->filehand, thefile->buffer, thefile->bufpos, &written, NULL))
-                rc = apr_get_os_error();
-            thefile->filePtr += written;
+            buffer = thefile->buffer;
+            bytesleft = thefile->bufpos;           
+
+            do {
+                if (bytesleft > APR_DWORD_MAX) {
+                    numbytes = APR_DWORD_MAX;
+                }
+                else {
+                    numbytes = (DWORD)bytesleft;
+                }
+
+                if (!WriteFile(thefile->filehand, buffer, numbytes, &written, NULL)) {
+                    rc = apr_get_os_error();
+                    thefile->filePtr += written;
+                    break;
+                }
+
+                thefile->filePtr += written;
+                bytesleft -= written;
+                buffer += written;
+
+            } while (bytesleft > 0);
 
             if (rc == 0)
                 thefile->bufpos = 0;
         }
 
         return rc;
+    } else {
+        FlushFileBuffers(thefile->filehand);
+        return APR_SUCCESS;
     }
-
-    /* There isn't anything to do if we aren't buffering the output
-     * so just return success.
-     */
-    return APR_SUCCESS; 
 }
 
-struct apr_file_printf_data {
-    apr_vformatter_buff_t vbuff;
-    apr_file_t *fptr;
-    char *buf;
-};
-
-static int file_printf_flush(apr_vformatter_buff_t *buff)
+static int printf_flush(apr_vformatter_buff_t *vbuff)
 {
-    struct apr_file_printf_data *data = (struct apr_file_printf_data *)buff;
-
-    if (apr_file_write_full(data->fptr, data->buf,
-                            data->vbuff.curpos - data->buf, NULL)) {
-        return -1;
-    }
-
-    data->vbuff.curpos = data->buf;
-    return 0;
+    /* I would love to print this stuff out to the file, but I will
+     * get that working later.  :)  For now, just return.
+     */
+    return -1;
 }
 
 APR_DECLARE_NONSTD(int) apr_file_printf(apr_file_t *fptr, 
                                         const char *format, ...)
 {
-    struct apr_file_printf_data data;
+    int cc;
     va_list ap;
-    int count;
+    char *buf;
+    int len;
 
-    data.buf = malloc(HUGE_STRING_LEN);
-    if (data.buf == NULL) {
+    buf = malloc(HUGE_STRING_LEN);
+    if (buf == NULL) {
         return 0;
     }
-    data.vbuff.curpos = data.buf;
-    data.vbuff.endpos = data.buf + HUGE_STRING_LEN;
-    data.fptr = fptr;
     va_start(ap, format);
-    count = apr_vformatter(file_printf_flush,
-                           (apr_vformatter_buff_t *)&data, format, ap);
-    /* apr_vformatter does not call flush for the last bits */
-    if (count >= 0) file_printf_flush((apr_vformatter_buff_t *)&data);
-
+    len = apr_vsnprintf(buf, HUGE_STRING_LEN, format, ap);
+    cc = apr_file_puts(buf, fptr);
     va_end(ap);
-
-    free(data.buf);
-    return count;
+    free(buf);
+    return (cc == APR_SUCCESS) ? len : -1;
 }
+
+
