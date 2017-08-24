@@ -106,7 +106,7 @@ static int readmoredata(char *buffer,
 {
   struct connectdata *conn = (struct connectdata *)userp;
   struct HTTP *http = conn->proto.http;
-  int fullsize = size * nitems;
+  int fullsize = (int)(size * nitems);
 
   if(0 == http->postsize)
     /* nothing to return */
@@ -195,7 +195,7 @@ CURLcode add_buffer_send(send_buffer *in,
      to the circumstances we will just loop and try again and again etc */
 
   ptr = in->buffer;
-  size = in->size_used;
+  size = (int)in->size_used;
 
   res = Curl_write(conn, sockfd, ptr, size, &amount);
 
@@ -274,7 +274,7 @@ CURLcode add_buffer(send_buffer *in, const void *inptr, size_t size)
 
   if(!in->buffer ||
      ((in->size_used + size) > (in->size_max - 1))) {
-    new_size = (in->size_used+size)*2;
+    new_size = (int)((in->size_used+size)*2);
     if(in->buffer)
       /* we have a buffer, enlarge the existing one */
       new_rb = (char *)realloc(in->buffer, new_size);
@@ -666,7 +666,8 @@ CURLcode Curl_http(struct connectdata *conn)
        curl_strequal(data->state.auth_host, conn->hostname)) {
       sprintf(data->state.buffer, "%s:%s",
               data->state.user, data->state.passwd);
-      if(Curl_base64_encode(data->state.buffer, strlen(data->state.buffer),
+      if(Curl_base64_encode(data->state.buffer, 
+                            (int)strlen(data->state.buffer),
                             &authorization) >= 0) {
         if(conn->allocptr.userpwd)
           free(conn->allocptr.userpwd);
@@ -804,7 +805,7 @@ CURLcode Curl_http(struct connectdata *conn)
         if(readthisamountnow > BUFSIZE)
           readthisamountnow = BUFSIZE;
 
-        actuallyread =
+        actuallyread = (int)
           data->set.fread(data->state.buffer, 1, readthisamountnow,
                           data->set.in);
 
@@ -1125,9 +1126,9 @@ CURLcode Curl_http(struct connectdata *conn)
       /* and here we setup the pointers to the actual data */
       if(data->set.postfields) {
         if(data->set.postfieldsize)
-          http->postsize = data->set.postfieldsize;
+          http->postsize = (int)data->set.postfieldsize;
         else
-          http->postsize = strlen(data->set.postfields);
+          http->postsize = (int)strlen(data->set.postfields);
         http->postdata = data->set.postfields;
 
         http->sending = HTTPSEND_BODY;