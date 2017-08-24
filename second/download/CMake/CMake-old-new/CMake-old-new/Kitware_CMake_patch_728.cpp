@@ -1,28 +1,29 @@
-/*****************************************************************************
+/***************************************************************************
  *                                  _   _ ____  _     
  *  Project                     ___| | | |  _ \| |    
  *                             / __| | | | |_) | |    
  *                            | (__| |_| |  _ <| |___ 
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 2000, Daniel Stenberg, <daniel@haxx.se>, et al.
- *
- * In order to be useful for every potential user, curl and libcurl are
- * dual-licensed under the MPL and the MIT/X-derivate licenses.
+ * Copyright (C) 1998 - 2002, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
+ * This software is licensed as described in the file COPYING, which
+ * you should have received as part of this distribution. The terms
+ * are also available at http://curl.haxx.se/docs/copyright.html.
+ * 
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
- * furnished to do so, under the terms of the MPL or the MIT/X-derivate
- * licenses. You may pick one of these licenses.
+ * furnished to do so, under the terms of the COPYING file.
  *
  * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
  * KIND, either express or implied.
  *
  * $Id$
- *****************************************************************************/
+ ***************************************************************************/
 
 #include "setup.h"
 
+#ifndef CURL_DISABLE_HTTP
 /* -- WIN32 approved -- */
 #include <stdio.h>
 #include <string.h>
@@ -133,12 +134,6 @@ CURLcode add_buffer_send(int sockfd, struct connectdata *conn, send_buffer *in,
   char *ptr;
   int size;
 
-  if(conn->data->set.verbose) {
-    fputs("> ", conn->data->set.err);
-    /* this data _may_ contain binary stuff */
-    fwrite(in->buffer, in->size_used, 1, conn->data->set.err);
-  }
-
   /* The looping below is required since we use non-blocking sockets, but due
      to the circumstances we will just loop and try again and again etc */
 
@@ -150,6 +145,10 @@ CURLcode add_buffer_send(int sockfd, struct connectdata *conn, send_buffer *in,
     if(CURLE_OK != res)
       break;
 
+    if(conn->data->set.verbose)
+      /* this data _may_ contain binary stuff */
+      Curl_debug(conn->data, CURLINFO_HEADER_OUT, ptr, amount);
+
     if(amount != size) {
       size -= amount;
       ptr += amount;
@@ -163,7 +162,7 @@ CURLcode add_buffer_send(int sockfd, struct connectdata *conn, send_buffer *in,
     free(in->buffer);
   free(in);
 
-  *bytes_written = amount;
+  *bytes_written += amount;
 
   return res;
 }
@@ -364,11 +363,8 @@ CURLcode Curl_ConnectHTTPProxyTunnel(struct connectdata *conn,
                the line isn't really terminated until the LF comes */
 
             /* output debug output if that is requested */
-            if(data->set.verbose) {
-              fputs("< ", data->set.err);
-              fwrite(line_start, perline, 1, data->set.err);
-              /* no need to output LF here, it is part of the data */
-            }
+            if(data->set.verbose)
+              Curl_debug(data, CURLINFO_DATA_IN, line_start, perline);
             
             if('\r' == line_start[0]) {
               /* end of headers */
@@ -392,15 +388,15 @@ CURLcode Curl_ConnectHTTPProxyTunnel(struct connectdata *conn,
   } /* while there's buffer left and loop is requested */
 
   if(error)
-    return CURLE_READ_ERROR;
+    return CURLE_RECV_ERROR;
 
   if(200 != httperror) {
     if(407 == httperror)
       /* Added Nov 6 1998 */
       failf(data, "Proxy requires authorization!");
     else 
       failf(data, "Received error code %d from proxy", httperror);
-    return CURLE_READ_ERROR;
+    return CURLE_RECV_ERROR;
   }
 
   infof (data, "Proxy replied to CONNECT request\n");
@@ -424,7 +420,7 @@ CURLcode Curl_http_connect(struct connectdata *conn)
    * has occured, can we start talking SSL
    */
 
-  if(data->change.proxy &&
+  if(conn->bits.httpproxy &&
      ((conn->protocol & PROT_HTTPS) || data->set.tunnel_thru_httpproxy)) {
 
     /* either HTTPS over proxy, OR explicitly asked for a tunnel */
@@ -453,23 +449,21 @@ CURLcode Curl_http_connect(struct connectdata *conn)
 CURLcode Curl_http_done(struct connectdata *conn)
 {
   struct SessionHandle *data;
-  long *bytecount = &conn->bytecount;
   struct HTTP *http;
 
   data=conn->data;
   http=conn->proto.http;
 
   if(HTTPREQ_POST_FORM == data->set.httpreq) {
-    *bytecount = http->readbytecount + http->writebytecount;
+    conn->bytecount = http->readbytecount + http->writebytecount;
       
     Curl_formclean(http->sendit); /* Now free that whole lot */
 
     data->set.fread = http->storefread; /* restore */
     data->set.in = http->in; /* restore */
   }
-  else if(HTTPREQ_PUT == data->set.httpreq) {
-    *bytecount = http->readbytecount + http->writebytecount;
-  }
+  else if(HTTPREQ_PUT == data->set.httpreq)
+    conn->bytecount = http->readbytecount + http->writebytecount;
 
   if(0 == (http->readbytecount + conn->headerbytecount)) {
     /* nothing was read from the HTTP server, this can't be right
@@ -491,7 +485,7 @@ CURLcode Curl_http(struct connectdata *conn)
   struct Cookie *co=NULL; /* no cookies from start */
   char *ppath = conn->ppath; /* three previous function arguments */
   char *host = conn->name;
-  long *bytecount = &conn->bytecount;
+  const char *te = ""; /* tranfer-encoding */
 
   if(!conn->proto.http) {
     /* Only allocate this struct if we don't already have it! */
@@ -553,12 +547,20 @@ CURLcode Curl_http(struct connectdata *conn)
     conn->allocptr.cookie = aprintf("Cookie: %s\015\012", data->set.cookie);
   }
 
+  if(conn->bits.upload_chunky) {
+    if(!checkheaders(data, "Transfer-Encoding:")) {
+      te = "Transfer-Encoding: chunked\r\n";
+    }
+    /* else
+       our header was already added, what to do now? */
+  }
+
   if(data->cookies) {
     co = Curl_cookie_getlist(data->cookies,
                              host, ppath,
-                             conn->protocol&PROT_HTTPS?TRUE:FALSE);
+                             (conn->protocol&PROT_HTTPS?TRUE:FALSE));
   }
-  if (data->change.proxy &&
+  if (data->change.proxy && *data->change.proxy &&
       !data->set.tunnel_thru_httpproxy &&
       !(conn->protocol&PROT_HTTPS))  {
     /* The path sent to the proxy is in fact the entire URL */
@@ -567,7 +569,13 @@ CURLcode Curl_http(struct connectdata *conn)
   if(HTTPREQ_POST_FORM == data->set.httpreq) {
     /* we must build the whole darned post sequence first, so that we have
        a size of the whole shebang before we start to send it */
-    http->sendit = Curl_getFormData(data->set.httppost, &http->postsize);
+     result = Curl_getFormData(&http->sendit, data->set.httppost,
+                               &http->postsize);
+     if(CURLE_OK != result) {
+       /* Curl_getFormData() doesn't use failf() */
+       failf(data, "failed creating formpost data");
+       return result;
+     }
   }
 
   if(!checkheaders(data, "Host:")) {
@@ -579,13 +587,22 @@ CURLcode Curl_http(struct connectdata *conn)
     if(conn->allocptr.host)
       free(conn->allocptr.host);
 
+    /* When building Host: headers, we must put the host name within
+       [brackets] if the host name is a plain IPv6-address. RFC2732-style. */
+       
     if(((conn->protocol&PROT_HTTPS) && (conn->remote_port == PORT_HTTPS)) ||
        (!(conn->protocol&PROT_HTTPS) && (conn->remote_port == PORT_HTTP)) )
       /* If (HTTPS on port 443) OR (non-HTTPS on port 80) then don't include
          the port number in the host string */
-      conn->allocptr.host = aprintf("Host: %s\r\n", host);
+      conn->allocptr.host = aprintf("Host: %s%s%s\r\n",
+                                    conn->bits.ipv6_ip?"[":"",
+                                    host,
+                                    conn->bits.ipv6_ip?"]":"");
     else
-      conn->allocptr.host = aprintf("Host: %s:%d\r\n", host,
+      conn->allocptr.host = aprintf("Host: %s%s%s:%d\r\n",
+                                    conn->bits.ipv6_ip?"[":"",
+                                    host,
+                                    conn->bits.ipv6_ip?"]":"",
                                     conn->remote_port);
   }
 
@@ -661,6 +678,9 @@ CURLcode Curl_http(struct connectdata *conn)
      */
     if((data->set.httpreq == HTTPREQ_GET) &&
        !checkheaders(data, "Range:")) {
+      /* if a line like this was already allocated, free the previous one */
+      if(conn->allocptr.rangeline)
+        free(conn->allocptr.rangeline);
       conn->allocptr.rangeline = aprintf("Range: bytes=%s\r\n", conn->range);
     }
     else if((data->set.httpreq != HTTPREQ_GET) &&
@@ -705,7 +725,9 @@ CURLcode Curl_http(struct connectdata *conn)
                 "%s" /* host */
                 "%s" /* pragma */
                 "%s" /* accept */
-                "%s", /* referer */
+                "%s" /* accept-encoding */
+                "%s" /* referer */
+                "%s",/* transfer-encoding */
 
                 data->set.customrequest?data->set.customrequest:
                 (data->set.no_body?"HEAD":
@@ -725,7 +747,10 @@ CURLcode Curl_http(struct connectdata *conn)
                 (conn->allocptr.host?conn->allocptr.host:""), /* Host: host */
                 http->p_pragma?http->p_pragma:"",
                 http->p_accept?http->p_accept:"",
-                (data->change.referer && conn->allocptr.ref)?conn->allocptr.ref:"" /* Referer: <data> <CRLF> */
+                (data->set.encoding && *data->set.encoding && conn->allocptr.accept_encoding)?
+                conn->allocptr.accept_encoding:"", /* 08/28/02 jhrg */
+                (data->change.referer && conn->allocptr.ref)?conn->allocptr.ref:"" /* Referer: <data> <CRLF> */,
+                te
                 );
 
     if(co) {
@@ -780,16 +805,16 @@ CURLcode Curl_http(struct connectdata *conn)
       strcpy(buf, "no strftime() support");
 #endif
       switch(data->set.timecondition) {
-      case TIMECOND_IFMODSINCE:
+      case CURL_TIMECOND_IFMODSINCE:
       default:
         add_bufferf(req_buffer,
                     "If-Modified-Since: %s\r\n", buf);
         break;
-      case TIMECOND_IFUNMODSINCE:
+      case CURL_TIMECOND_IFUNMODSINCE:
         add_bufferf(req_buffer,
                     "If-Unmodified-Since: %s\r\n", buf);
         break;
-      case TIMECOND_LASTMOD:
+      case CURL_TIMECOND_LASTMOD:
         add_bufferf(req_buffer,
                     "Last-Modified: %s\r\n", buf);
         break;
@@ -814,7 +839,9 @@ CURLcode Curl_http(struct connectdata *conn)
       headers = headers->next;
     }
 
-    if(HTTPREQ_POST_FORM == data->set.httpreq) {
+    switch(data->set.httpreq) {
+
+    case HTTPREQ_POST_FORM:
       if(Curl_FormInit(&http->form, http->sendit)) {
         failf(data, "Internal HTTP POST error!");
         return CURLE_HTTP_POST_ERROR;
@@ -883,9 +910,9 @@ CURLcode Curl_http(struct connectdata *conn)
         Curl_formclean(http->sendit); /* free that whole lot */
         return result;
       }
-    }
-    else if(HTTPREQ_PUT == data->set.httpreq) {
-      /* Let's PUT the data to the server! */
+      break;
+
+    case HTTPREQ_PUT: /* Let's PUT the data to the server! */
 
       if(data->set.infilesize>0) {
         add_bufferf(req_buffer,
@@ -911,51 +938,53 @@ CURLcode Curl_http(struct connectdata *conn)
                                &http->writebytecount);
       if(result)
         return result;
-      
-    }
-    else {
-      if(HTTPREQ_POST == data->set.httpreq) {
-        /* this is the simple POST, using x-www-form-urlencoded style */
-
-        if(!data->set.postfields) {
-          /*
-           * This is an attempt to do a POST without having anything to
-           * actually send. Let's make a NULL pointer equal "" here. Good/bad
-           * ?
-           */
-          data->set.postfields = (char *)"";
-          data->set.postfieldsize = 0; /* it might been set to something illegal,
-                                      anything > 0 would be! */
-        }
+      break;
 
-        if(!checkheaders(data, "Content-Length:"))
-          /* we allow replacing this header, although it isn't very wise to
-             actually set your own */
-          add_bufferf(req_buffer,
-                      "Content-Length: %d\r\n",
-                      (data->set.postfieldsize?data->set.postfieldsize:
-                       strlen(data->set.postfields)) );
+    case HTTPREQ_POST:
+      /* this is the simple POST, using x-www-form-urlencoded style */
 
-        if(!checkheaders(data, "Content-Type:"))
-          add_bufferf(req_buffer,
-                      "Content-Type: application/x-www-form-urlencoded\r\n");
+      if(!checkheaders(data, "Content-Length:"))
+        /* we allow replacing this header, although it isn't very wise to
+           actually set your own */
+        add_bufferf(req_buffer,
+                    "Content-Length: %d\r\n",
+                    data->set.postfieldsize?
+                    data->set.postfieldsize:
+                    (data->set.postfields?strlen(data->set.postfields):0) );
 
-        /* and here comes the actual data */
-        if(data->set.postfieldsize) {
-          add_buffer(req_buffer, "\r\n", 2);
-          add_buffer(req_buffer, data->set.postfields,
-                     data->set.postfieldsize);
-        }
-        else {
-          add_bufferf(req_buffer,
-                      "\r\n"
-                      "%s",
-                      data->set.postfields );
-        }
+      if(!checkheaders(data, "Content-Type:"))
+        add_bufferf(req_buffer,
+                    "Content-Type: application/x-www-form-urlencoded\r\n");
+
+      add_buffer(req_buffer, "\r\n", 2);
+
+      /* and here comes the actual data */
+      if(data->set.postfieldsize && data->set.postfields) {
+        add_buffer(req_buffer, data->set.postfields,
+                   data->set.postfieldsize);
       }
+      else if(data->set.postfields)
+        add_bufferf(req_buffer,
+                    "%s",
+                    data->set.postfields );
+
+      /* issue the request */
+      result = add_buffer_send(conn->firstsocket, conn, req_buffer,
+                               &data->info.request_size);
+
+      if(result)
+        failf(data, "Failed sending HTTP POST request");
       else
-        add_buffer(req_buffer, "\r\n", 2);
+        result =
+          Curl_Transfer(conn, conn->firstsocket, -1, TRUE,
+                        &http->readbytecount,
+                        data->set.postfields?-1:conn->firstsocket,
+                        data->set.postfields?NULL:&http->writebytecount);
+      break;
 
+    default:
+      add_buffer(req_buffer, "\r\n", 2);
+      
       /* issue the request */
       result = add_buffer_send(conn->firstsocket, conn, req_buffer,
                                &data->info.request_size);
@@ -964,7 +993,8 @@ CURLcode Curl_http(struct connectdata *conn)
         failf(data, "Failed sending HTTP request");
       else
         /* HTTP GET/HEAD download: */
-        result = Curl_Transfer(conn, conn->firstsocket, -1, TRUE, bytecount,
+        result = Curl_Transfer(conn, conn->firstsocket, -1, TRUE,
+                               &http->readbytecount,
                                -1, NULL); /* nothing to upload */
     }
     if(result)
@@ -983,3 +1013,4 @@ CURLcode Curl_http(struct connectdata *conn)
  * vim600: fdm=marker
  * vim: et sw=2 ts=2 sts=2 tw=78
  */
+#endif