@@ -1,25 +1,25 @@
-/*****************************************************************************
+/***************************************************************************
  *                                  _   _ ____  _     
  *  Project                     ___| | | |  _ \| |    
  *                             / __| | | | |_) | |    
  *                            | (__| |_| |  _ <| |___ 
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 2001, Daniel Stenberg, <daniel@haxx.se>, et al.
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
 
@@ -82,6 +82,8 @@
 #include <curl/types.h>
 #include "netrc.h"
 
+#include "content_encoding.h"   /* content encoding support. 08/27/02 jhrg */
+
 #include "hostip.h"
 #include "transfer.h"
 #include "sendf.h"
@@ -168,6 +170,10 @@ compareheader(char *headerline, /* line to check */
   return FALSE; /* no match */
 }
 
+/* We keep this static and global since this is read-only and NEVER
+   changed. It should just remain a blanked-out timeout value. */
+static struct timeval notimeout={0,0};
+
 CURLcode Curl_readwrite(struct connectdata *conn,
                         bool *done)
 {
@@ -176,14 +182,49 @@ CURLcode Curl_readwrite(struct connectdata *conn,
   int result;
   ssize_t nread; /* number of bytes read */
   int didwhat=0;
+  
+  /* These two are used only if no other select() or _fdset() have been
+     invoked before this. This typicly happens if you use the multi interface
+     and call curl_multi_perform() without calling curl_multi_fdset()
+     first. */
+  fd_set extrareadfd;
+  fd_set extrawritefd;
+
+  fd_set *readfdp = k->readfdp;
+  fd_set *writefdp = k->writefdp;
+  
+  if((k->keepon & KEEP_READ) && !readfdp) {
+    /* reading is requested, but no socket descriptor pointer was set */
+    FD_ZERO(&extrareadfd);
+    FD_SET(conn->sockfd, &extrareadfd);
+    readfdp = &extrareadfd;
+
+    /* no write, no exceptions, no timeout */
+    select(conn->sockfd+1, readfdp, NULL, NULL, &notimeout);
+  }
+  if((k->keepon & KEEP_WRITE) && !writefdp) {
+    /* writing is requested, but no socket descriptor pointer was set */
+    FD_ZERO(&extrawritefd);
+    FD_SET(conn->writesockfd, &extrawritefd);
+    writefdp = &extrawritefd;
+
+    /* no read, no exceptions, no timeout */
+    select(conn->writesockfd+1, NULL, writefdp, NULL, &notimeout);
+  }
 
   do {
+    /* If we still have reading to do, we check if we have a readable
+       socket. Sometimes the reafdp is NULL, it no fd_set was done using
+       the multi interface and then we can do nothing but to attempt a
+       read to be sure. */
     if((k->keepon & KEEP_READ) &&
-       FD_ISSET(conn->sockfd, &k->readfd)) {
+       (FD_ISSET(conn->sockfd, readfdp))) {
 
       /* read! */
       result = Curl_read(conn, conn->sockfd, k->buf,
-                         BUFSIZE -1, &nread);
+                         data->set.buffer_size?
+                         data->set.buffer_size:BUFSIZE -1,
+                         &nread);
 
       if(0>result)
         break; /* get out of loop */
@@ -215,6 +256,7 @@ CURLcode Curl_readwrite(struct connectdata *conn,
          headers at the moment or not. */          
       if (k->header) {
         /* we are in parse-the-header-mode */
+        bool stop_reading = FALSE;
 
         /* header line within buffer loop */
         do {
@@ -226,35 +268,43 @@ CURLcode Curl_readwrite(struct connectdata *conn,
           k->end_ptr = strchr (k->str_start, '\n');
               
           if (!k->end_ptr) {
-            /* no more complete header lines within buffer */
-            /* copy what is remaining into headerbuff */
-            int str_length = (int)strlen(k->str);
+            /* Not a complete header line within buffer, append the data to
+               the end of the headerbuff. */
 
-            /*
-             * We enlarge the header buffer if it seems to be too
-             * smallish
-             */
-            if (k->hbuflen + (int)str_length >=
-                data->state.headersize) {
+            if (k->hbuflen + nread >= data->state.headersize) {
+              /* We enlarge the header buffer as it is too small */
               char *newbuff;
-              long newsize=MAX((k->hbuflen+str_length)*3/2,
+              long newsize=MAX((k->hbuflen+nread)*3/2,
                                data->state.headersize*2);
               hbufp_index = k->hbufp - data->state.headerbuff;
               newbuff = (char *)realloc(data->state.headerbuff, newsize);
               if(!newbuff) {
                 failf (data, "Failed to alloc memory for big header!");
-                return CURLE_READ_ERROR;
+                return CURLE_OUT_OF_MEMORY;
               }
               data->state.headersize=newsize;
               data->state.headerbuff = newbuff;
               k->hbufp = data->state.headerbuff + hbufp_index;
             }
-            strcpy (k->hbufp, k->str);
-            k->hbufp += strlen (k->str);
-            k->hbuflen += strlen (k->str);
+            memcpy(k->hbufp, k->str, nread);
+            k->hbufp += nread;
+            k->hbuflen += nread;
+            if (!k->headerline && (k->hbuflen>5)) {
+              /* make a first check that this looks like a HTTP header */
+              if(!checkprefix("HTTP/", data->state.headerbuff)) {
+                /* this is not the beginning of a HTTP first header line */
+                k->header = FALSE;
+                k->badheader = HEADER_ALLBAD;
+                break;
+              }
+            }
+
             break;              /* read more and try again */
           }
 
+          /* decrease the size of the remaining buffer */
+          nread -= (k->end_ptr - k->str)+1; 
+
           k->str = k->end_ptr + 1; /* move past new line */
 
           /*
@@ -273,7 +323,7 @@ CURLcode Curl_readwrite(struct connectdata *conn,
             newbuff = (char *)realloc(data->state.headerbuff, newsize);
             if(!newbuff) {
               failf (data, "Failed to alloc memory for big header!");
-              return CURLE_READ_ERROR;
+              return CURLE_OUT_OF_MEMORY;
             }
             data->state.headersize= newsize;
             data->state.headerbuff = newbuff;
@@ -292,7 +342,19 @@ CURLcode Curl_readwrite(struct connectdata *conn,
            * We now have a FULL header line that p points to
            *****/
 
+          if(!k->headerline) {
+            /* the first read header */
+            if((k->hbuflen>5) &&
+               !checkprefix("HTTP/", data->state.headerbuff)) {
+              /* this is not the beginning of a HTTP first header line */
+              k->header = FALSE;
+              k->badheader = HEADER_PARTHEADER;
+              break;
+            }
+          }
+
           if (('\n' == *k->p) || ('\r' == *k->p)) {
+            int headerlen;
             /* Zero-length header line means end of headers! */
 
             if ('\r' == *k->p)
@@ -327,7 +389,7 @@ CURLcode Curl_readwrite(struct connectdata *conn,
                * we got: "417 Expectation Failed" this means:
                * we have made a HTTP call and our Expect Header
                * seems to cause a problem => abort the write operations
-               * (or prevent them from starting
+               * (or prevent them from starting).
                */
               k->write_after_100_header = FALSE;
               k->keepon &= ~KEEP_WRITE;
@@ -340,14 +402,16 @@ CURLcode Curl_readwrite(struct connectdata *conn,
             if (data->set.http_include_header)
               k->writetype |= CLIENTWRITE_BODY;
 
+            headerlen = k->p - data->state.headerbuff;
+
             result = Curl_client_write(data, k->writetype,
                                        data->state.headerbuff,
-                                       k->p - data->state.headerbuff);
+                                       headerlen);
             if(result)
               return result;
 
-            data->info.header_size += k->p - data->state.headerbuff;
-            conn->headerbytecount += k->p - data->state.headerbuff;
+            data->info.header_size += headerlen;
+            conn->headerbytecount += headerlen;
 
             if(!k->header) {
               /*
@@ -356,8 +420,6 @@ CURLcode Curl_readwrite(struct connectdata *conn,
                * If we requested a "no body", this is a good time to get
                * out and return home.
                */
-              bool stop_reading = FALSE;
-
               if(data->set.no_body)
                 stop_reading = TRUE;
               else if(!conn->bits.close) {
@@ -367,22 +429,16 @@ CURLcode Curl_readwrite(struct connectdata *conn,
                    reading! */
                 if(-1 != conn->size)
                   conn->maxdownload = conn->size;
-
-                /* If max download size is *zero* (nothing) we already
-                   have nothing and can safely return ok now! */
-                if(0 == conn->maxdownload)
-                  stop_reading = TRUE;
-                    
-                /* What to do if the size is *not* known? */
               }
-
+              /* If max download size is *zero* (nothing) we already
+                 have nothing and can safely return ok now! */
+              if(0 == conn->maxdownload)
+                stop_reading = TRUE;
+                    
               if(stop_reading) {
                 /* we make sure that this socket isn't read more now */
                 k->keepon &= ~KEEP_READ;
                 FD_ZERO(&k->rkeepfd);
-                /* for a progress meter/info update before going away */
-                Curl_pgrsUpdate(conn);
-                return CURLE_OK;
               }
 
               break;            /* exit header line loop */
@@ -451,29 +507,31 @@ CURLcode Curl_readwrite(struct connectdata *conn,
                  * NOT contain a message-body, and thus is always terminated
                  * by the first empty line after the header fields.  */
                 conn->size=0;
+                conn->maxdownload=0;
                 break;
               default:
                 /* nothing */
                 break;
               }
             }
             else {
-              k->header = FALSE;        /* this is not a header line */
+              k->header = FALSE;   /* this is not a header line */
               break;
             }
           }
+
           /* check for Content-Length: header lines to get size */
-          if (strnequal("Content-Length:", k->p, 15) &&
+          if (checkprefix("Content-Length:", k->p) &&
               sscanf (k->p+15, " %ld", &k->contentlength)) {
             conn->size = k->contentlength;
             Curl_pgrsSetDownloadSize(data, k->contentlength);
-          }
+            }
           /* check for Content-Type: header lines to get the mime-type */
-          else if (strnequal("Content-Type:", k->p, 13)) {
+          else if (checkprefix("Content-Type:", k->p)) {
             char *start;
             char *end;
             int len;
-
+              
             /* Find the first non-space letter */
             for(start=k->p+14;
                 *start && isspace((int)*start);
@@ -539,7 +597,35 @@ CURLcode Curl_readwrite(struct connectdata *conn,
             /* init our chunky engine */
             Curl_httpchunk_init(conn);
           }
-          else if (strnequal("Content-Range:", k->p, 14)) {
+          else if (checkprefix("Content-Encoding:", k->p) &&
+                   data->set.encoding) {
+            /*
+             * Process Content-Encoding. Look for the values: identity, gzip,
+             * defalte, compress, x-gzip and x-compress. x-gzip and
+             * x-compress are the same as gzip and compress. (Sec 3.5 RFC
+             * 2616). zlib cannot handle compress, and gzip is not currently
+             * implemented. However, errors are handled further down when the
+             * response body is processed 08/27/02 jhrg */
+            char *start;
+
+            /* Find the first non-space letter */
+            for(start=k->p+17;
+                *start && isspace((int)*start);
+                start++);
+
+            /* Record the content-encoding for later use. 08/27/02 jhrg */
+            if (checkprefix("identity", start))
+              k->content_encoding = IDENTITY;
+            else if (checkprefix("deflate", start))
+              k->content_encoding = DEFLATE;
+            else if (checkprefix("gzip", start) 
+                     || checkprefix("x-gzip", start))
+              k->content_encoding = GZIP;
+            else if (checkprefix("compress", start) 
+                     || checkprefix("x-compress", start))
+              k->content_encoding = COMPRESS;
+          }
+          else if (checkprefix("Content-Range:", k->p)) {
             if (sscanf (k->p+14, " bytes %d-", &k->offset) ||
                 sscanf (k->p+14, " bytes: %d-", &k->offset)) {
               /* This second format was added August 1st 2000 by Igor
@@ -552,11 +638,10 @@ CURLcode Curl_readwrite(struct connectdata *conn,
             }
           }
           else if(data->cookies &&
-                  strnequal("Set-Cookie:", k->p, 11)) {
-            Curl_cookie_add(data->cookies, TRUE, k->p+12, conn->name);
+                  checkprefix("Set-Cookie:", k->p)) {
+            Curl_cookie_add(data->cookies, TRUE, k->p+11, conn->name);
           }
-          else if(strnequal("Last-Modified:", k->p,
-                            strlen("Last-Modified:")) &&
+          else if(checkprefix("Last-Modified:", k->p) &&
                   (data->set.timecondition || data->set.get_filetime) ) {
             time_t secs=time(NULL);
             k->timeofdoc = curl_getdate(k->p+strlen("Last-Modified:"),
@@ -566,7 +651,7 @@ CURLcode Curl_readwrite(struct connectdata *conn,
           }
           else if ((k->httpcode >= 300 && k->httpcode < 400) &&
                    (data->set.http_follow_location) &&
-                   strnequal("Location:", k->p, 9)) {
+                   checkprefix("Location:", k->p)) {
             /* this is the URL that the server advices us to get instead */
             char *ptr;
             char *start=k->p;
@@ -584,9 +669,11 @@ CURLcode Curl_readwrite(struct connectdata *conn,
             while(*ptr && !isspace((int)*ptr))
               ptr++;
             backup = *ptr; /* store the ending letter */
-            *ptr = '\0';   /* zero terminate */
-            conn->newurl = strdup(start); /* clone string */
-            *ptr = backup; /* restore ending letter */
+            if(ptr != start) {
+              *ptr = '\0';   /* zero terminate */
+              conn->newurl = strdup(start); /* clone string */
+              *ptr = backup; /* restore ending letter */
+            }
           }
 
           /*
@@ -597,6 +684,10 @@ CURLcode Curl_readwrite(struct connectdata *conn,
           if (data->set.http_include_header)
             k->writetype |= CLIENTWRITE_BODY;
 
+          if(data->set.verbose)
+            Curl_debug(data, CURLINFO_HEADER_IN,
+                       k->p, k->hbuflen);
+
           result = Curl_client_write(data, k->writetype, k->p,
                                      k->hbuflen);
           if(result)
@@ -609,20 +700,16 @@ CURLcode Curl_readwrite(struct connectdata *conn,
           k->hbufp = data->state.headerbuff;
           k->hbuflen = 0;
         }
-        while (*k->str); /* header line within buffer */
+        while (!stop_reading && *k->str); /* header line within buffer */
+
+        if(stop_reading)
+          /* We've stopped dealing with input, get out of the do-while loop */
+          break;
 
         /* We might have reached the end of the header part here, but
            there might be a non-header part left in the end of the read
            buffer. */
 
-        if (!k->header) {
-          /* the next token and forward is not part of
-             the header! */
-
-          /* we subtract the remaining header size from the buffer */
-          nread -= (k->str - k->buf);
-        }
-
       }                 /* end if header mode */
 
       /* This is not an 'else if' since it may be a rest from the header
@@ -638,8 +725,9 @@ CURLcode Curl_readwrite(struct connectdata *conn,
             if (conn->newurl) {
               /* abort after the headers if "follow Location" is set */
               infof (data, "Follow to new URL: %s\n", conn->newurl);
-                k->keepon &= ~KEEP_READ;
-                FD_ZERO(&k->rkeepfd);
+              k->keepon &= ~KEEP_READ;
+              FD_ZERO(&k->rkeepfd);
+              *done = TRUE;
               return CURLE_OK;
             }
             else if (conn->resume_from &&
@@ -664,13 +752,15 @@ CURLcode Curl_readwrite(struct connectdata *conn,
                   if(k->timeofdoc < data->set.timevalue) {
                     infof(data,
                           "The requested document is not new enough\n");
+                    *done = TRUE;
                     return CURLE_OK;
                   }
                   break;
                 case TIMECOND_IFUNMODSINCE:
                   if(k->timeofdoc > data->set.timevalue) {
                     infof(data,
                           "The requested document is not old enough\n");
+                    *done = TRUE;
                     return CURLE_OK;
                   }
                   break;
@@ -682,6 +772,18 @@ CURLcode Curl_readwrite(struct connectdata *conn,
         } /* this is the first time we write a body part */
         k->bodywrites++;
 
+        /* pass data to the debug function before it gets "dechunked" */
+        if(data->set.verbose) {
+          if(k->badheader) {
+            Curl_debug(data, CURLINFO_DATA_IN, data->state.headerbuff,
+                       k->hbuflen);
+            if(k->badheader == HEADER_PARTHEADER)
+              Curl_debug(data, CURLINFO_DATA_IN, k->str, nread);
+          }
+          else
+            Curl_debug(data, CURLINFO_DATA_IN, k->str, nread);
+        }
+
         if(conn->bits.chunk) {
           /*
            * Bless me father for I have sinned. Here comes a chunked
@@ -693,8 +795,12 @@ CURLcode Curl_readwrite(struct connectdata *conn,
             Curl_httpchunk_read(conn, k->str, nread, &nread);
 
           if(CHUNKE_OK < res) {
-            failf(data, "Receeived problem in the chunky parser");
-            return CURLE_READ_ERROR;
+            if(CHUNKE_WRITE_ERROR == res) {
+              failf(data, "Failed writing data");
+              return CURLE_WRITE_ERROR;
+            }
+            failf(data, "Received problem in the chunky parser");
+            return CURLE_RECV_ERROR;
           }
           else if(CHUNKE_STOP == res) {
             /* we're done reading chunks! */
@@ -722,19 +828,64 @@ CURLcode Curl_readwrite(struct connectdata *conn,
 
         Curl_pgrsSetDownloadCounter(data, (double)k->bytecount);
             
-        if(!conn->bits.chunk && nread) {
+        if(!conn->bits.chunk && (nread || k->badheader)) {
           /* If this is chunky transfer, it was already written */
-          result = Curl_client_write(data, CLIENTWRITE_BODY, k->str,
-                                     nread);
+
+          if(k->badheader) {
+            /* we parsed a piece of data wrongly assuming it was a header
+               and now we output it as body instead */
+            result = Curl_client_write(data, CLIENTWRITE_BODY,
+                                       data->state.headerbuff,
+                                       k->hbuflen);
+          }
+          if(k->badheader < HEADER_ALLBAD) {
+            /* This switch handles various content encodings. If there's an
+               error here, be sure to check over the almost identical code in
+               http_chunk.c. 08/29/02 jhrg */
+#ifdef HAVE_LIBZ
+            switch (k->content_encoding) {
+            case IDENTITY:
+#endif
+              /* This is the default when the server sends no
+                 Content-Encoding header. See Curl_readwrite_init; the
+                 memset() call initializes k->content_encoding to zero.
+                 08/28/02 jhrg */
+              result = Curl_client_write(data, CLIENTWRITE_BODY, k->str, 
+                                         nread);
+#ifdef HAVE_LIBZ
+              break;
+
+            case DEFLATE: 
+              /* Assume CLIENTWRITE_BODY; headers are not encoded. */
+              result = Curl_unencode_deflate_write(data, k, nread);
+              break;
+
+            case GZIP:          /* FIXME 08/27/02 jhrg */
+            case COMPRESS:
+            default:
+              failf (data, "Unrecognized content encoding type. "
+                     "libcurl understands `identity' and `deflate' "
+                     "content encodings.");
+              result = CURLE_BAD_CONTENT_ENCODING;
+              break;
+            }
+#endif
+          }
+          k->badheader = HEADER_NORMAL; /* taken care of now */
+
           if(result)
             return result;
         }
 
       } /* if (! header and data to read ) */
     } /* if( read from socket ) */
 
+    /* If we still have writing to do, we check if we have a writable
+       socket. Sometimes the writefdp is NULL, it no fd_set was done using
+       the multi interface and then we can do nothing but to attempt a
+       write to be sure. */
     if((k->keepon & KEEP_WRITE) &&
-       FD_ISSET(conn->writesockfd, &k->writefd)) {
+       (FD_ISSET(conn->writesockfd, writefdp)) ) {
       /* write */
 
       int i, si;
@@ -748,11 +899,46 @@ CURLcode Curl_readwrite(struct connectdata *conn,
       /* only read more data if there's no upload data already
          present in the upload buffer */
       if(0 == conn->upload_present) {
+        size_t buffersize = BUFSIZE;
         /* init the "upload from here" pointer */
         conn->upload_fromhere = k->uploadbuf;
 
-        nread = data->set.fread(conn->upload_fromhere, 1,
-                                BUFSIZE, data->set.in);
+        if(!k->upload_done) {
+
+          if(conn->bits.upload_chunky) {
+            /* if chunked Transfer-Encoding */
+            buffersize -= (8 + 2 + 2);   /* 32bit hex + CRLF + CRLF */
+            conn->upload_fromhere += 10; /* 32bit hex + CRLF */
+          }
+
+          nread = data->set.fread(conn->upload_fromhere, 1,
+                                  buffersize, data->set.in);
+          
+          if(conn->bits.upload_chunky) {
+            /* if chunked Transfer-Encoding */
+            char hexbuffer[9];
+            int hexlen = snprintf(hexbuffer, sizeof(hexbuffer),
+                                  "%x\r\n", nread);
+            /* move buffer pointer */
+            conn->upload_fromhere -= hexlen;
+            nread += hexlen;
+
+            /* copy the prefix to the buffer */
+            memcpy(conn->upload_fromhere, hexbuffer, hexlen);
+            if(nread>0) {
+              /* append CRLF to the data */
+              memcpy(conn->upload_fromhere +
+                     nread, "\r\n", 2);
+              nread+=2;
+            }
+            else {
+              /* mark this as done once this chunk is transfered */
+              k->upload_done = TRUE;
+            }
+          }
+        }
+        else
+          nread = 0; /* we're done uploading/reading */
 
         /* the signed int typecase of nread of for systems that has
            unsigned size_t */
@@ -769,16 +955,24 @@ CURLcode Curl_readwrite(struct connectdata *conn,
         /* convert LF to CRLF if so asked */
         if (data->set.crlf) {
           for(i = 0, si = 0; i < nread; i++, si++) {
-            if (k->buf[i] == 0x0a) {
+            if (conn->upload_fromhere[i] == 0x0a) {
               data->state.scratch[si++] = 0x0d;
               data->state.scratch[si] = 0x0a;
             }
-            else {
-              data->state.scratch[si] = k->uploadbuf[i];
-            }
+            else
+              data->state.scratch[si] = conn->upload_fromhere[i];
+          }
+          if(si != nread) {
+            /* only perform the special operation if we really did replace
+               anything */
+            nread = si;
+
+            /* upload from the new (replaced) buffer instead */
+            conn->upload_fromhere = data->state.scratch;
+
+            /* set the new amount too */
+            conn->upload_present = nread;
           }
-          nread = si;
-          k->buf = data->state.scratch; /* point to the new buffer */
         }
       }
       else {
@@ -804,14 +998,23 @@ CURLcode Curl_readwrite(struct connectdata *conn,
            is to happen */
         conn->upload_fromhere += bytes_written;
       }
-      else if(data->set.crlf)
-        k->buf = data->state.buffer; /* put it back on the buffer */
       else {
         /* we've uploaded that buffer now */
         conn->upload_fromhere = k->uploadbuf;
         conn->upload_present = 0; /* no more bytes left */
+
+        if(k->upload_done) {
+          /* switch off writing, we're done! */
+          k->keepon &= ~KEEP_WRITE; /* we're done writing */
+          FD_ZERO(&k->wkeepfd);
+        }
       }
 
+      if(data->set.verbose)
+        Curl_debug(data, CURLINFO_DATA_OUT, conn->upload_fromhere,
+                   bytes_written);
+      
+
       k->writebytecount += bytes_written;
       Curl_pgrsSetUploadCounter(data, (double)k->writebytecount);
 
@@ -887,13 +1090,14 @@ CURLcode Curl_readwrite_init(struct connectdata *conn)
   struct SessionHandle *data = conn->data;
   struct Curl_transfer_keeper *k = &conn->keep;
 
+  /* NB: the content encoding software depends on this initialization of
+     Curl_transfer_keeper. 08/28/02 jhrg */
   memset(k, 0, sizeof(struct Curl_transfer_keeper));
 
   k->start = Curl_tvnow(); /* start time */
   k->now = k->start;   /* current time is now */
   k->header = TRUE; /* assume header */
   k->httpversion = -1; /* unknown at this point */
-  k->conn = (struct connectdata *)conn; /* store the connection */
 
   data = conn->data; /* there's the root struct */
   k->buf = data->state.buffer;
@@ -905,13 +1109,16 @@ CURLcode Curl_readwrite_init(struct connectdata *conn)
   Curl_pgrsTime(data, TIMER_PRETRANSFER);
   Curl_speedinit(data);
 
-  if (!conn->getheader) {
+  Curl_pgrsSetUploadCounter(data, 0);
+  Curl_pgrsSetDownloadCounter(data, 0);
+
+  if (!conn->bits.getheader) {
     k->header = FALSE;
     if(conn->size > 0)
       Curl_pgrsSetDownloadSize(data, conn->size);
   }
   /* we want header and/or body, if neither then don't do this! */
-  if(conn->getheader || !data->set.no_body) {
+  if(conn->bits.getheader || !data->set.no_body) {
 
     FD_ZERO (&k->readfd);               /* clear it */
     if(conn->sockfd != -1) {
@@ -950,11 +1157,13 @@ void Curl_single_fdset(struct connectdata *conn,
   if(conn->keep.keepon & KEEP_READ) {
     FD_SET(conn->sockfd, read_fd_set);
     *max_fd = conn->sockfd;
+    conn->keep.readfdp = read_fd_set; /* store the address of the set */
   }
   if(conn->keep.keepon & KEEP_WRITE) {
     FD_SET(conn->writesockfd, write_fd_set);
     if(conn->writesockfd > *max_fd)
       *max_fd = conn->writesockfd;
+    conn->keep.writefdp = write_fd_set; /* store the address of the set */
   }
   /* we don't use exceptions, only touch that one to prevent compiler
      warnings! */
@@ -991,18 +1200,20 @@ Transfer(struct connectdata *conn)
     return CURLE_OK;
 
   /* we want header and/or body, if neither then don't do this! */
-  if(!conn->getheader && data->set.no_body)
+  if(!conn->bits.getheader && data->set.no_body)
     return CURLE_OK;
 
+  k->writefdp = &k->writefd; /* store the address of the set */
+  k->readfdp = &k->readfd;   /* store the address of the set */
+
   while (!done) {
     struct timeval interval;
     k->readfd = k->rkeepfd;  /* set these every lap in the loop */
     k->writefd = k->wkeepfd;
     interval.tv_sec = 1;
     interval.tv_usec = 0;
 
-    switch (select (k->maxfd, &k->readfd, &k->writefd, NULL,
-                    &interval)) {
+    switch (select (k->maxfd, k->readfdp, k->writefdp, NULL, &interval)) {
     case -1: /* select() error, stop reading */
 #ifdef EINTR
       /* The EINTR is not serious, and it seems you might get this more
@@ -1047,6 +1258,22 @@ CURLcode Curl_pretransfer(struct SessionHandle *data)
   data->state.this_is_a_follow = FALSE; /* reset this */
   data->state.errorbuf = FALSE; /* no error has occurred */
 
+  /* If there was a list of cookie files to read and we haven't done it before,
+     do it now! */
+  if(data->change.cookielist) {
+    struct curl_slist *list = data->change.cookielist;
+    while(list) {
+      data->cookies = Curl_cookie_init(list->data,
+                                       data->cookies,
+                                       data->set.cookiesession);
+      list = list->next;
+    }
+    curl_slist_free_all(data->change.cookielist); /* clean up list */
+    data->change.cookielist = NULL; /* don't do this again! */
+  }
+
+
+
  /* Allow data->set.use_port to set which port to use. This needs to be
   * disabled for example when we follow Location: headers to URLs using
   * different ports! */
@@ -1056,7 +1283,8 @@ CURLcode Curl_pretransfer(struct SessionHandle *data)
   /*************************************************************
    * Tell signal handler to ignore SIGPIPE
    *************************************************************/
-  data->state.prev_signal = signal(SIGPIPE, SIG_IGN);
+  if(!data->set.no_signal)
+    data->state.prev_signal = signal(SIGPIPE, SIG_IGN);
 #endif  
 
   Curl_initinfo(data); /* reset session-specific information "variables" */
@@ -1069,28 +1297,263 @@ CURLcode Curl_posttransfer(struct SessionHandle *data)
 {
 #if defined(HAVE_SIGNAL) && defined(SIGPIPE)
   /* restore the signal handler for SIGPIPE before we get back */
-  signal(SIGPIPE, data->state.prev_signal);
+  if(!data->set.no_signal)
+    signal(SIGPIPE, data->state.prev_signal);
 #endif  
 
   return CURLE_OK;
 }
 
+CURLcode Curl_follow(struct SessionHandle *data,
+                     char *newurl) /* this 'newurl' is the Location: string,
+                                      and it must be malloc()ed before passed
+                                      here */
+{
+  /* Location: redirect */
+  char prot[16]; /* URL protocol string storage */
+  char letter;   /* used for a silly sscanf */
+  
+  if (data->set.maxredirs &&
+      (data->set.followlocation >= data->set.maxredirs)) {
+    failf(data,"Maximum (%d) redirects followed", data->set.maxredirs);
+    return CURLE_TOO_MANY_REDIRECTS;
+  }
+
+  /* mark the next request as a followed location: */
+  data->state.this_is_a_follow = TRUE;
+
+  data->set.followlocation++; /* count location-followers */
+
+  if(data->set.http_auto_referer) {
+    /* We are asked to automatically set the previous URL as the
+       referer when we get the next URL. We pick the ->url field,
+       which may or may not be 100% correct */
+
+    if(data->change.referer_alloc)
+      /* If we already have an allocated referer, free this first */
+      free(data->change.referer);
+
+    data->change.referer = strdup(data->change.url);
+    data->change.referer_alloc = TRUE; /* yes, free this later */
+  }
+
+  if(2 != sscanf(newurl, "%15[^?&/:]://%c", prot, &letter)) {
+    /***
+     *DANG* this is an RFC 2068 violation. The URL is supposed
+     to be absolute and this doesn't seem to be that!
+     ***
+     Instead, we have to TRY to append this new path to the old URL
+     to the right of the host part. Oh crap, this is doomed to cause
+     problems in the future...
+    */
+    char *protsep;
+    char *pathsep;
+    char *newest;
+
+    char *useurl = newurl;
+
+    /* we must make our own copy of the URL to play with, as it may
+       point to read-only data */
+    char *url_clone=strdup(data->change.url);
+
+    if(!url_clone)
+      return CURLE_OUT_OF_MEMORY; /* skip out of this NOW */
+
+    /* protsep points to the start of the host name */
+    protsep=strstr(url_clone, "//");
+    if(!protsep)
+      protsep=url_clone;
+    else
+      protsep+=2; /* pass the slashes */
+
+    if('/' != newurl[0]) {
+      int level=0;
+
+      /* First we need to find out if there's a ?-letter in the URL,
+         and cut it and the right-side of that off */
+      pathsep = strrchr(protsep, '?');
+      if(pathsep)
+        *pathsep=0;
+      
+      /* we have a relative path to append to the last slash if
+         there's one available */
+      pathsep = strrchr(protsep, '/');
+      if(pathsep)
+        *pathsep=0;
+
+      /* Check if there's any slash after the host name, and if so,
+         remember that position instead */
+      pathsep = strchr(protsep, '/');
+      if(pathsep)
+        protsep = pathsep+1;
+      else
+        protsep = NULL;
+
+      /* now deal with one "./" or any amount of "../" in the newurl
+         and act accordingly */
+
+      if((useurl[0] == '.') && (useurl[1] == '/'))
+        useurl+=2; /* just skip the "./" */
+            
+      while((useurl[0] == '.') &&
+            (useurl[1] == '.') &&
+            (useurl[2] == '/')) {
+        level++; 
+        useurl+=3; /* pass the "../" */
+      }
+
+      if(protsep) {
+        while(level--) {
+          /* cut off one more level from the right of the original URL */
+          pathsep = strrchr(protsep, '/');
+          if(pathsep)
+            *pathsep=0;
+          else {
+            *protsep=0;
+            break;
+          }
+        }
+      }
+    }
+    else {
+      /* We got a new absolute path for this server, cut off from the
+         first slash */
+      pathsep = strchr(protsep, '/');
+      if(pathsep)
+        *pathsep=0;
+    }
+
+    newest=(char *)malloc( strlen(url_clone) +
+                           1 + /* possible slash */
+                           strlen(useurl) + 1/* zero byte */);
+    
+    if(!newest)
+      return CURLE_OUT_OF_MEMORY; /* go out from this */
+
+    sprintf(newest, "%s%s%s", url_clone,
+            (('/' == useurl[0]) || (protsep && !*protsep))?"":"/",
+            useurl);
+    free(newurl); /* newurl is the allocated pointer */
+    free(url_clone);
+    newurl = newest;
+  }
+  else
+    /* This is an absolute URL, don't allow the custom port number */
+    data->state.allow_port = FALSE;
+
+  if(data->change.url_alloc)
+    free(data->change.url);
+  else
+    data->change.url_alloc = TRUE; /* the URL is allocated */
+      
+  /* TBD: set the URL with curl_setopt() */
+  data->change.url = newurl;
+  newurl = NULL; /* don't free! */
+
+  infof(data, "Follows Location: to new URL: '%s'\n", data->change.url);
+
+  /*
+   * We get here when the HTTP code is 300-399. We need to perform
+   * differently based on exactly what return code there was.
+   * Discussed on the curl mailing list and posted about on the 26th
+   * of January 2001.
+   */
+  switch(data->info.httpcode) {
+  case 300: /* Multiple Choices */
+  case 306: /* Not used */
+  case 307: /* Temporary Redirect */
+  default:  /* for all unknown ones */
+    /* These are explicitly mention since I've checked RFC2616 and they
+     * seem to be OK to POST to.
+     */
+    break;
+  case 301: /* Moved Permanently */
+    /* (quote from RFC2616, section 10.3.2):
+     * 
+     *  Note: When automatically redirecting a POST request after
+     *  receiving a 301 status code, some existing HTTP/1.0 user agents
+     *  will erroneously change it into a GET request.
+     *
+     * ----
+     * Warning: Because most of importants user agents do this clear
+     * RFC2616 violation, many webservers expect this misbehavior. So
+     * these servers often answers to a POST request with an error page.
+     * To be sure that libcurl gets the page that most user agents
+     * would get, libcurl has to force GET:
+     */
+    if( data->set.httpreq == HTTPREQ_POST
+        || data->set.httpreq == HTTPREQ_POST_FORM) {
+      infof(data,
+            "Violate RFC 2616/10.3.2 and switch from POST to GET\n");
+      data->set.httpreq = HTTPREQ_GET;
+    }
+    break;
+  case 302: /* Found */
+    /* (From 10.3.3)
+       
+    Note: RFC 1945 and RFC 2068 specify that the client is not allowed
+    to change the method on the redirected request.  However, most
+    existing user agent implementations treat 302 as if it were a 303
+    response, performing a GET on the Location field-value regardless
+    of the original request method. The status codes 303 and 307 have
+    been added for servers that wish to make unambiguously clear which
+    kind of reaction is expected of the client.
+    
+    (From 10.3.4)
+    
+    Note: Many pre-HTTP/1.1 user agents do not understand the 303
+    status. When interoperability with such clients is a concern, the
+    302 status code may be used instead, since most user agents react
+    to a 302 response as described here for 303.             
+    */
+  case 303: /* See Other */
+    /* Disable both types of POSTs, since doing a second POST when
+     * following isn't what anyone would want! */
+    if(data->set.httpreq != HTTPREQ_GET) {
+      data->set.httpreq = HTTPREQ_GET; /* enforce GET request */
+      infof(data, "Disables POST, goes with %s\n",
+            data->set.no_body?"HEAD":"GET");
+    }
+    break;
+  case 304: /* Not Modified */
+    /* 304 means we did a conditional request and it was "Not modified".
+     * We shouldn't get any Location: header in this response!
+     */
+    break;
+  case 305: /* Use Proxy */
+    /* (quote from RFC2616, section 10.3.6):
+     * "The requested resource MUST be accessed through the proxy given
+     * by the Location field. The Location field gives the URI of the
+     * proxy.  The recipient is expected to repeat this single request
+     * via the proxy. 305 responses MUST only be generated by origin
+     * servers."
+     */
+    break;
+  }
+  Curl_pgrsTime(data, TIMER_REDIRECT);
+  Curl_pgrsResetTimes(data);
+
+  return CURLE_OK;
+}
+
 CURLcode Curl_perform(struct SessionHandle *data)
 {
   CURLcode res;
   CURLcode res2;
   struct connectdata *conn=NULL;
   char *newurl = NULL; /* possibly a new URL to follow to! */
 
+  data->state.used_interface = Curl_if_easy;
+
   res = Curl_pretransfer(data);
   if(res)
     return res;
 
   /*
-   * It is important that there is NO 'return' from this function any any
-   * other place than falling down the bottom! This is because we have cleanup
-   * stuff that must be done before we get back, and that is only performed
-   * after this do-while loop.
+   * It is important that there is NO 'return' from this function at any other
+   * place than falling down to the end of the function! This is because we
+   * have cleanup stuff that must be done before we get back, and that is only
+   * performed after this do-while loop.
    */
 
   do {
@@ -1116,12 +1579,20 @@ CURLcode Curl_perform(struct SessionHandle *data)
            * may be free()ed in the Curl_done() function.
            */
           newurl = conn->newurl?strdup(conn->newurl):NULL;
-        else
+        else {
           /* The transfer phase returned error, we mark the connection to get
            * closed to prevent being re-used. This is becasue we can't
            * possibly know if the connection is in a good shape or not now. */
           conn->bits.close = TRUE;
 
+          if(-1 !=conn->secondarysocket) {
+            /* if we failed anywhere, we must clean up the secondary socket if
+               it was used */
+            sclose(conn->secondarysocket);
+            conn->secondarysocket=-1;
+          }
+        }
+
         /* Always run Curl_done(), even if some of the previous calls
            failed, but return the previous (original) error code */
         res2 = Curl_done(conn);
@@ -1136,172 +1607,11 @@ CURLcode Curl_perform(struct SessionHandle *data)
        */
 
       if((res == CURLE_OK) && newurl) {
-        /* Location: redirect
- 
-           This is assumed to happen for HTTP(S) only!
-        */
-        char prot[16]; /* URL protocol string storage */
-        char letter;   /* used for a silly sscanf */
-
-        if (data->set.maxredirs && (data->set.followlocation >= data->set.maxredirs)) {
-          failf(data,"Maximum (%d) redirects followed", data->set.maxredirs);
-          res=CURLE_TOO_MANY_REDIRECTS;
-          break;
-        }
-
-        /* mark the next request as a followed location: */
-        data->state.this_is_a_follow = TRUE;
-
-        data->set.followlocation++; /* count location-followers */
-
-        if(data->set.http_auto_referer) {
-          /* We are asked to automatically set the previous URL as the
-             referer when we get the next URL. We pick the ->url field,
-             which may or may not be 100% correct */
-
-          if(data->change.referer_alloc)
-            /* If we already have an allocated referer, free this first */
-            free(data->change.referer);
-
-          data->change.referer = strdup(data->change.url);
-          data->change.referer_alloc = TRUE; /* yes, free this later */
-        }
-
-        if(2 != sscanf(newurl, "%15[^?&/:]://%c", prot, &letter)) {
-          /***
-           *DANG* this is an RFC 2068 violation. The URL is supposed
-           to be absolute and this doesn't seem to be that!
-           ***
-           Instead, we have to TRY to append this new path to the old URL
-           to the right of the host part. Oh crap, this is doomed to cause
-           problems in the future...
-          */
-          char *protsep;
-          char *pathsep;
-          char *newest;
-
-          /* we must make our own copy of the URL to play with, as it may
-             point to read-only data */
-          char *url_clone=strdup(data->change.url);
-
-          if(!url_clone) {
-            res = CURLE_OUT_OF_MEMORY;
-            break; /* skip out of this loop NOW */
-          }
-
-          /* protsep points to the start of the host name */
-          protsep=strstr(url_clone, "//");
-          if(!protsep)
-            protsep=url_clone;
-          else
-            protsep+=2; /* pass the slashes */
-
-          if('/' != newurl[0]) {
-            /* First we need to find out if there's a ?-letter in the URL,
-               and cut it and the right-side of that off */
-            pathsep = strrchr(protsep, '?');
-            if(pathsep)
-              *pathsep=0;
-
-            /* we have a relative path to append to the last slash if
-               there's one available */
-            pathsep = strrchr(protsep, '/');
-            if(pathsep)
-              *pathsep=0;
-          }
-          else {
-            /* We got a new absolute path for this server, cut off from the
-               first slash */
-            pathsep = strchr(protsep, '/');
-            if(pathsep)
-              *pathsep=0;
-          }
-
-          newest=(char *)malloc( strlen(url_clone) +
-                                 1 + /* possible slash */
-                                 strlen(newurl) + 1/* zero byte */);
-
-          if(!newest) {
-            res = CURLE_OUT_OF_MEMORY;
-            break; /* go go go out from this loop */
-          }
-          sprintf(newest, "%s%s%s", url_clone, ('/' == newurl[0])?"":"/",
-                  newurl);
-          free(newurl);
-          free(url_clone);
-          newurl = newest;
-        }
-        else
-          /* This is an absolute URL, don't allow the custom port number */
-          data->state.allow_port = FALSE;
-
-        if(data->change.url_alloc)
-          free(data->change.url);
-        else
-          data->change.url_alloc = TRUE; /* the URL is allocated */
-      
-        /* TBD: set the URL with curl_setopt() */
-        data->change.url = newurl;
-        newurl = NULL; /* don't free! */
-
-        infof(data, "Follows Location: to new URL: '%s'\n", data->change.url);
-
-        /*
-         * We get here when the HTTP code is 300-399. We need to perform
-         * differently based on exactly what return code there was.
-         * Discussed on the curl mailing list and posted about on the 26th
-         * of January 2001.
-         */
-        switch(data->info.httpcode) {
-        case 300: /* Multiple Choices */
-        case 301: /* Moved Permanently */
-        case 306: /* Not used */
-        case 307: /* Temporary Redirect */
-        default:  /* for all unknown ones */
-          /* These are explicitly mention since I've checked RFC2616 and they
-           * seem to be OK to POST to.
-           */
-          break;
-        case 302: /* Found */
-          /* (From 10.3.3)
-
-            Note: RFC 1945 and RFC 2068 specify that the client is not allowed
-            to change the method on the redirected request.  However, most
-            existing user agent implementations treat 302 as if it were a 303
-            response, performing a GET on the Location field-value regardless
-            of the original request method. The status codes 303 and 307 have
-            been added for servers that wish to make unambiguously clear which
-            kind of reaction is expected of the client.
-
-            (From 10.3.4)
-
-            Note: Many pre-HTTP/1.1 user agents do not understand the 303
-            status. When interoperability with such clients is a concern, the
-            302 status code may be used instead, since most user agents react
-            to a 302 response as described here for 303.             
-          */
-        case 303: /* See Other */
-          /* Disable both types of POSTs, since doing a second POST when
-           * following isn't what anyone would want! */
-          data->set.httpreq = HTTPREQ_GET; /* enforce GET request */
-          infof(data, "Disables POST, goes with GET\n");
-          break;
-        case 304: /* Not Modified */
-          /* 304 means we did a conditional request and it was "Not modified".
-           * We shouldn't get any Location: header in this response!
-           */
-          break;
-        case 305: /* Use Proxy */
-          /* (quote from RFC2616, section 10.3.6):
-           * "The requested resource MUST be accessed through the proxy given
-           * by the Location field. The Location field gives the URI of the
-           * proxy.  The recipient is expected to repeat this single request
-           * via the proxy. 305 responses MUST only be generated by origin
-           * servers."
-           */
-          break;
+        res = Curl_follow(data, newurl);
+        if(CURLE_OK == res) {
+          newurl = NULL;
+          continue;
         }
-        continue;
       }
     }
     break; /* it only reaches here when this shouldn't loop */
@@ -1339,7 +1649,7 @@ Curl_Transfer(struct connectdata *c_conn, /* connection data */
   /* now copy all input parameters */
   conn->sockfd = sockfd;
   conn->size = size;
-  conn->getheader = getheader;
+  conn->bits.getheader = getheader;
   conn->bytecountp = bytecountp;
   conn->writesockfd = writesockfd;
   conn->writebytecountp = writebytecountp;