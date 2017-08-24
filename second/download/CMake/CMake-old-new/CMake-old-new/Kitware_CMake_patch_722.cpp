@@ -279,32 +279,6 @@ Curl_sec_write(struct connectdata *conn, int fd, char *buffer, int length)
 }
 
 int
-Curl_sec_vfprintf2(struct connectdata *conn, FILE *f, const char *fmt, va_list ap)
-{
-  char *buf;
-  int ret;
-  if(conn->data_prot == prot_clear)
-    return vfprintf(f, fmt, ap);
-  else {
-    buf = aprintf(fmt, ap);
-    ret = buffer_write(&conn->out_buffer, buf, strlen(buf));
-    free(buf);
-    return ret;
-  }
-}
-
-int
-Curl_sec_fprintf2(struct connectdata *conn, FILE *f, const char *fmt, ...)
-{
-    int ret;
-    va_list ap;
-    va_start(ap, fmt);
-    ret = Curl_sec_vfprintf2(conn, f, fmt, ap);
-    va_end(ap);
-    return ret;
-}
-
-int
 Curl_sec_putc(struct connectdata *conn, int c, FILE *F)
 {
   char ch = c;
@@ -313,7 +287,8 @@ Curl_sec_putc(struct connectdata *conn, int c, FILE *F)
     
   buffer_write(&conn->out_buffer, &ch, 1);
   if(c == '\n' || conn->out_buffer.index >= 1024 /* XXX */) {
-    Curl_sec_write(conn, fileno(F), conn->out_buffer.data, conn->out_buffer.index);
+    Curl_sec_write(conn, fileno(F), conn->out_buffer.data,
+                   conn->out_buffer.index);
     conn->out_buffer.index = 0;
   }
   return c;
@@ -346,53 +321,6 @@ Curl_sec_read_msg(struct connectdata *conn, char *s, int level)
     return code;
 }
 
-/* modified to return how many bytes written, or -1 on error ***/
-int
-Curl_sec_vfprintf(struct connectdata *conn, FILE *f, const char *fmt, va_list ap)
-{
-    int ret = 0;
-    char *buf;
-    void *enc;
-    int len;
-    if(!conn->sec_complete)
-        return vfprintf(f, fmt, ap);
-    
-    buf = aprintf(fmt, ap);
-    len = (conn->mech->encode)(conn->app_data, buf, strlen(buf),
-                               conn->command_prot, &enc,
-                               conn);
-    free(buf);
-    if(len < 0) {
-        failf(conn->data, "Failed to encode command.");
-        return -1;
-    }
-    if(Curl_base64_encode(enc, len, &buf) < 0){
-      failf(conn->data, "Out of memory base64-encoding.");
-      return -1;
-    }
-    if(conn->command_prot == prot_safe)
-        ret = fprintf(f, "MIC %s", buf);
-    else if(conn->command_prot == prot_private)
-        ret = fprintf(f, "ENC %s", buf);
-    else if(conn->command_prot == prot_confidential)
-        ret = fprintf(f, "CONF %s", buf);
-
-    free(buf);
-    return ret;
-}
-
-int
-Curl_sec_fprintf(struct connectdata *conn, FILE *f, const char *fmt, ...)
-{
-    va_list ap;
-    int ret;
-    va_start(ap, fmt);
-    ret = Curl_sec_vfprintf(conn, f, fmt, ap);
-    va_end(ap);
-    return ret;
-}
-
-
 enum protection_level
 Curl_set_command_prot(struct connectdata *conn, enum protection_level level)
 {
@@ -414,14 +342,14 @@ sec_prot_internal(struct connectdata *conn, int level)
   }
 
   if(level){
+    int code;
     if(Curl_ftpsendf(conn, "PBSZ %u", s))
       return -1;
 
-    nread = Curl_GetFTPResponse(conn->data->state.buffer, conn, NULL);
-    if(nread < 0)
+    if(Curl_GetFTPResponse(&nread, conn, &code))
       return -1;
 
-    if(conn->data->state.buffer[0] != '2'){
+    if(code/100 != '2'){
       failf(conn->data, "Failed to set protection buffer size.");
       return -1;
     }
@@ -437,8 +365,7 @@ sec_prot_internal(struct connectdata *conn, int level)
   if(Curl_ftpsendf(conn, "PROT %c", level["CSEP"]))
     return -1;
 
-  nread = Curl_GetFTPResponse(conn->data->state.buffer, conn, NULL);
-  if(nread < 0)
+  if(Curl_GetFTPResponse(&nread, conn, NULL))
     return -1;
 
   if(conn->data->state.buffer[0] != '2'){
@@ -496,8 +423,7 @@ Curl_sec_login(struct connectdata *conn)
     if(Curl_ftpsendf(conn, "AUTH %s", (*m)->name))
       return -1;
 
-    nread = Curl_GetFTPResponse(conn->data->state.buffer, conn, &ftpcode);
-    if(nread < 0)
+    if(Curl_GetFTPResponse(&nread, conn, &ftpcode))
       return -1;
 
     if(conn->data->state.buffer[0] != '3'){