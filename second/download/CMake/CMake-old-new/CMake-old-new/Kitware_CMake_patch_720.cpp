@@ -98,12 +98,65 @@
 #include "memdebug.h"
 #endif
 
+/* fread() emulation to provide POST and/or request data */
+static int readmoredata(char *buffer,
+                        size_t size,
+                        size_t nitems,
+                        void *userp)
+{
+  struct connectdata *conn = (struct connectdata *)userp;
+  struct HTTP *http = conn->proto.http;
+  int fullsize = size * nitems;
+
+  if(0 == http->postsize)
+    /* nothing to return */
+    return 0;
+  
+  /* make sure that a HTTP request is never sent away chunked! */
+  conn->bits.forbidchunk= (http->sending == HTTPSEND_REQUEST)?TRUE:FALSE;
+
+  if(http->postsize <= fullsize) {
+    memcpy(buffer, http->postdata, http->postsize);
+    fullsize = http->postsize;
+
+    if(http->backup.postsize) {
+      /* move backup data into focus and continue on that */
+      http->postdata = http->backup.postdata;
+      http->postsize = http->backup.postsize;
+      conn->fread =    http->backup.fread;
+      conn->fread_in = http->backup.fread_in;
+
+      http->sending++; /* move one step up */
+
+      http->backup.postsize=0;
+    }
+    else
+      http->postsize = 0;
+
+    return fullsize;
+  }
+
+  memcpy(buffer, http->postdata, fullsize);
+  http->postdata += fullsize;
+  http->postsize -= fullsize;
+
+  return fullsize;
+}
+
 /* ------------------------------------------------------------------------- */
 /*
  * The add_buffer series of functions are used to build one large memory chunk
  * from repeated function invokes. Used so that the entire HTTP request can
  * be sent in one go.
  */
+
+struct send_buffer {
+  char *buffer;
+  size_t size_max;
+  size_t size_used;
+};
+typedef struct send_buffer send_buffer;
+
 static CURLcode
  add_buffer(send_buffer *in, const void *inptr, size_t size);
 
@@ -126,44 +179,66 @@ send_buffer *add_buffer_init(void)
  * add_buffer_send() sends a buffer and frees all associated memory.
  */
 static
-CURLcode add_buffer_send(int sockfd, struct connectdata *conn, send_buffer *in,
-                         long *bytes_written)
+CURLcode add_buffer_send(send_buffer *in,
+                         int sockfd,
+                         struct connectdata *conn,
+                         long *bytes_written) /* add the number of sent
+                                                 bytes to this counter */
 {
   ssize_t amount;
   CURLcode res;
   char *ptr;
   int size;
+  struct HTTP *http = conn->proto.http;
 
   /* The looping below is required since we use non-blocking sockets, but due
      to the circumstances we will just loop and try again and again etc */
 
   ptr = in->buffer;
   size = in->size_used;
-  do {
-    res = Curl_write(conn, sockfd, ptr, size, &amount);
 
-    if(CURLE_OK != res)
-      break;
+  res = Curl_write(conn, sockfd, ptr, size, &amount);
+
+  if(CURLE_OK == res) {
 
     if(conn->data->set.verbose)
       /* this data _may_ contain binary stuff */
       Curl_debug(conn->data, CURLINFO_HEADER_OUT, ptr, amount);
 
+    *bytes_written += amount;
+    
     if(amount != size) {
+      /* The whole request could not be sent in one system call. We must queue
+         it up and send it later when we get the chance. We must not loop here
+         and wait until it might work again. */
+
       size -= amount;
       ptr += amount;
+    
+      /* backup the currently set pointers */
+      http->backup.fread = conn->fread;
+      http->backup.fread_in = conn->fread_in;
+      http->backup.postdata = http->postdata;
+      http->backup.postsize = http->postsize;
+
+      /* set the new pointers for the request-sending */
+      conn->fread = (curl_read_callback)readmoredata;
+      conn->fread_in = (void *)conn;
+      http->postdata = ptr;
+      http->postsize = size;
+
+      http->send_buffer = in;
+      http->sending = HTTPSEND_REQUEST;
+      
+      return CURLE_OK;
     }
-    else
-      break;
-
-  } while(1);
 
+    /* the full buffer was sent, clean up and return */
+  }
   if(in->buffer)
     free(in->buffer);
   free(in);
 
-  *bytes_written += amount;
-
   return res;
 }
 
@@ -224,20 +299,74 @@ CURLcode add_buffer(send_buffer *in, const void *inptr, size_t size)
 /* ------------------------------------------------------------------------- */
 
 /*
+ * Curl_compareheader()
+ *
+ * Returns TRUE if 'headerline' contains the 'header' with given 'content'.
+ * Pass headers WITH the colon.
+ */
+bool
+Curl_compareheader(char *headerline,    /* line to check */
+                   const char *header,  /* header keyword _with_ colon */
+                   const char *content) /* content string to find */
+{
+  /* RFC2616, section 4.2 says: "Each header field consists of a name followed
+   * by a colon (":") and the field value. Field names are case-insensitive.
+   * The field value MAY be preceded by any amount of LWS, though a single SP
+   * is preferred." */
+
+  size_t hlen = strlen(header);
+  size_t clen;
+  size_t len;
+  char *start;
+  char *end;
+
+  if(!strnequal(headerline, header, hlen))
+    return FALSE; /* doesn't start with header */
+
+  /* pass the header */
+  start = &headerline[hlen];
+
+  /* pass all white spaces */
+  while(*start && isspace((int)*start))
+    start++;
+
+  /* find the end of the header line */
+  end = strchr(start, '\r'); /* lines end with CRLF */
+  if(!end) {
+    /* in case there's a non-standard compliant line here */
+    end = strchr(start, '\n');
+
+    if(!end)
+      /* hm, there's no line ending here, use the zero byte! */
+      end = strchr(start, '\0');
+  }
+
+  len = end-start; /* length of the content part of the input line */
+  clen = strlen(content); /* length of the word to find */
+
+  /* find the content string in the rest of the line */
+  for(;len>=clen;len--, start++) {
+    if(strnequal(start, content, clen))
+      return TRUE; /* match! */
+  }
+
+  return FALSE; /* no match */
+}
+
+/*
  * This function checks the linked list of custom HTTP headers for a particular
  * header (prefix).
  */
-static bool checkheaders(struct SessionHandle *data, const char *thisheader)
+static char *checkheaders(struct SessionHandle *data, const char *thisheader)
 {
   struct curl_slist *head;
   size_t thislen = strlen(thisheader);
 
   for(head = data->set.headers; head; head=head->next) {
-    if(strnequal(head->data, thisheader, thislen)) {
-      return TRUE;
-    }
+    if(strnequal(head->data, thisheader, thislen))
+      return head->data;
   }
-  return FALSE;
+  return NULL;
 }
 
 /*
@@ -440,6 +569,10 @@ CURLcode Curl_http_connect(struct connectdata *conn)
   if(conn->bits.user_passwd && !data->state.this_is_a_follow) {
     /* Authorization: is requested, this is not a followed location, get the
        original host name */
+    if (data->state.auth_host)
+      /* Free to avoid leaking memory on multiple requests*/
+      free(data->state.auth_host);
+
     data->state.auth_host = strdup(conn->hostname);
   }
 
@@ -454,13 +587,21 @@ CURLcode Curl_http_done(struct connectdata *conn)
   data=conn->data;
   http=conn->proto.http;
 
+  /* set the proper values (possibly modified on POST) */
+  conn->fread = data->set.fread; /* restore */
+  conn->fread_in = data->set.in; /* restore */
+
+  if(http->send_buffer) {
+    send_buffer *buff = http->send_buffer;
+    
+    free(buff->buffer);
+    free(buff);
+  }
+
   if(HTTPREQ_POST_FORM == data->set.httpreq) {
     conn->bytecount = http->readbytecount + http->writebytecount;
       
     Curl_formclean(http->sendit); /* Now free that whole lot */
-
-    data->set.fread = http->storefread; /* restore */
-    data->set.in = http->in; /* restore */
   }
   else if(HTTPREQ_PUT == data->set.httpreq)
     conn->bytecount = http->readbytecount + http->writebytecount;
@@ -475,7 +616,6 @@ CURLcode Curl_http_done(struct connectdata *conn)
   return CURLE_OK;
 }
 
-
 CURLcode Curl_http(struct connectdata *conn)
 {
   struct SessionHandle *data=conn->data;
@@ -523,7 +663,7 @@ CURLcode Curl_http(struct connectdata *conn)
        host due to a location-follow, we do some weirdo checks here */
     if(!data->state.this_is_a_follow ||
        !data->state.auth_host ||
-       strequal(data->state.auth_host, conn->hostname)) {
+       curl_strequal(data->state.auth_host, conn->hostname)) {
       sprintf(data->state.buffer, "%s:%s",
               data->state.user, data->state.passwd);
       if(Curl_base64_encode(data->state.buffer, strlen(data->state.buffer),
@@ -547,12 +687,30 @@ CURLcode Curl_http(struct connectdata *conn)
     conn->allocptr.cookie = aprintf("Cookie: %s\015\012", data->set.cookie);
   }
 
+  if(!conn->bits.upload_chunky && (data->set.httpreq != HTTPREQ_GET)) {
+    /* not a chunky transfer but data is to be sent */
+    char *ptr = checkheaders(data, "Transfer-Encoding:");
+    if(ptr) {
+      /* Some kind of TE is requested, check if 'chunked' is chosen */
+      if(Curl_compareheader(ptr, "Transfer-Encoding:", "chunked"))
+        /* we have been told explicitly to upload chunky so deal with it! */
+        conn->bits.upload_chunky = TRUE;
+    }
+  }
+
   if(conn->bits.upload_chunky) {
+    /* RFC2616 section 4.4:
+       Messages MUST NOT include both a Content-Length header field and a
+       non-identity transfer-coding. If the message does include a non-
+       identity transfer-coding, the Content-Length MUST be ignored. */
+
     if(!checkheaders(data, "Transfer-Encoding:")) {
       te = "Transfer-Encoding: chunked\r\n";
     }
-    /* else
-       our header was already added, what to do now? */
+    else {
+      /* The "Transfer-Encoding:" header was already added. */
+      te = "";
+    }
   }
 
   if(data->cookies) {
@@ -847,16 +1005,16 @@ CURLcode Curl_http(struct connectdata *conn)
         return CURLE_HTTP_POST_ERROR;
       }
 
-      http->storefread = data->set.fread; /* backup */
-      http->in = data->set.in; /* backup */
-          
-      data->set.fread = (curl_read_callback)
-        Curl_FormReader; /* set the read function to read from the
-                            generated form data */
-      data->set.in = (FILE *)&http->form;
+      /* set the read function to read from the generated form data */
+      conn->fread = (curl_read_callback)Curl_FormReader;
+      conn->fread_in = &http->form;
 
-      add_bufferf(req_buffer,
-                  "Content-Length: %d\r\n", http->postsize);
+      http->sending = HTTPSEND_BODY;
+
+      if(!conn->bits.upload_chunky)
+        /* only add Content-Length if not uploading chunked */
+        add_bufferf(req_buffer,
+                    "Content-Length: %d\r\n", http->postsize);
 
       if(!checkheaders(data, "Expect:")) {
         /* if not disabled explicitly we add a Expect: 100-continue
@@ -896,7 +1054,7 @@ CURLcode Curl_http(struct connectdata *conn)
       Curl_pgrsSetUploadSize(data, http->postsize);
 
       /* fire away the whole request to the server */
-      result = add_buffer_send(conn->firstsocket, conn, req_buffer,
+      result = add_buffer_send(req_buffer, conn->firstsocket, conn, 
                                &data->info.request_size);
       if(result)
         failf(data, "Failed sending POST request");
@@ -914,22 +1072,22 @@ CURLcode Curl_http(struct connectdata *conn)
 
     case HTTPREQ_PUT: /* Let's PUT the data to the server! */
 
-      if(data->set.infilesize>0) {
+      if((data->set.infilesize>0) && !conn->bits.upload_chunky)
+        /* only add Content-Length if not uploading chunked */
         add_bufferf(req_buffer,
-                    "Content-Length: %d\r\n\r\n", /* file size */
+                    "Content-Length: %d\r\n", /* file size */
                     data->set.infilesize );
-      }
-      else
-        add_bufferf(req_buffer, "\015\012");
+
+      add_bufferf(req_buffer, "\r\n");
 
       /* set the upload size to the progress meter */
       Curl_pgrsSetUploadSize(data, data->set.infilesize);
 
       /* this sends the buffer and frees all the buffer resources */
-      result = add_buffer_send(conn->firstsocket, conn, req_buffer,
+      result = add_buffer_send(req_buffer, conn->firstsocket, conn,
                                &data->info.request_size);
       if(result)
-        failf(data, "Faied sending POST request");
+        failf(data, "Failed sending POST request");
       else
         /* prepare for transfer */
         result = Curl_Transfer(conn, conn->firstsocket, -1, TRUE,
@@ -943,33 +1101,49 @@ CURLcode Curl_http(struct connectdata *conn)
     case HTTPREQ_POST:
       /* this is the simple POST, using x-www-form-urlencoded style */
 
-      if(!checkheaders(data, "Content-Length:"))
-        /* we allow replacing this header, although it isn't very wise to
-           actually set your own */
-        add_bufferf(req_buffer,
-                    "Content-Length: %d\r\n",
-                    data->set.postfieldsize?
-                    data->set.postfieldsize:
-                    (data->set.postfields?strlen(data->set.postfields):0) );
+      if(!conn->bits.upload_chunky) {
+        /* We only set Content-Length and allow a custom Content-Length if
+           we don't upload data chunked, as RFC2616 forbids us to set both
+           kinds of headers (Transfer-Encoding: chunked and Content-Length) */
+
+        if(!checkheaders(data, "Content-Length:"))
+          /* we allow replacing this header, although it isn't very wise to
+             actually set your own */
+          add_bufferf(req_buffer,
+                      "Content-Length: %d\r\n",
+                      data->set.postfieldsize?
+                      data->set.postfieldsize:
+                      (data->set.postfields?strlen(data->set.postfields):0) );
+      }
 
       if(!checkheaders(data, "Content-Type:"))
         add_bufferf(req_buffer,
                     "Content-Type: application/x-www-form-urlencoded\r\n");
 
       add_buffer(req_buffer, "\r\n", 2);
 
-      /* and here comes the actual data */
-      if(data->set.postfieldsize && data->set.postfields) {
-        add_buffer(req_buffer, data->set.postfields,
-                   data->set.postfieldsize);
+      /* and here we setup the pointers to the actual data */
+      if(data->set.postfields) {
+        if(data->set.postfieldsize)
+          http->postsize = data->set.postfieldsize;
+        else
+          http->postsize = strlen(data->set.postfields);
+        http->postdata = data->set.postfields;
+
+        http->sending = HTTPSEND_BODY;
+
+        conn->fread = (curl_read_callback)readmoredata;
+        conn->fread_in = (void *)conn;
+
+        /* set the upload size to the progress meter */
+        Curl_pgrsSetUploadSize(data, http->postsize);
       }
-      else if(data->set.postfields)
-        add_bufferf(req_buffer,
-                    "%s",
-                    data->set.postfields );
+      else
+        /* set the upload size to the progress meter */
+        Curl_pgrsSetUploadSize(data, data->set.infilesize);
 
-      /* issue the request */
-      result = add_buffer_send(conn->firstsocket, conn, req_buffer,
+      /* issue the request, headers-only */
+      result = add_buffer_send(req_buffer, conn->firstsocket, conn,
                                &data->info.request_size);
 
       if(result)
@@ -978,15 +1152,15 @@ CURLcode Curl_http(struct connectdata *conn)
         result =
           Curl_Transfer(conn, conn->firstsocket, -1, TRUE,
                         &http->readbytecount,
-                        data->set.postfields?-1:conn->firstsocket,
-                        data->set.postfields?NULL:&http->writebytecount);
+                        conn->firstsocket,
+                        &http->writebytecount);
       break;
 
     default:
       add_buffer(req_buffer, "\r\n", 2);
       
       /* issue the request */
-      result = add_buffer_send(conn->firstsocket, conn, req_buffer,
+      result = add_buffer_send(req_buffer, conn->firstsocket, conn,
                                &data->info.request_size);
 
       if(result)
@@ -995,7 +1169,8 @@ CURLcode Curl_http(struct connectdata *conn)
         /* HTTP GET/HEAD download: */
         result = Curl_Transfer(conn, conn->firstsocket, -1, TRUE,
                                &http->readbytecount,
-                               -1, NULL); /* nothing to upload */
+                               http->postdata?conn->firstsocket:-1,
+                               http->postdata?&http->writebytecount:NULL);
     }
     if(result)
       return result;