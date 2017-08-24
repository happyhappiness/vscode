@@ -1,25 +1,25 @@
-/*****************************************************************************
+/***************************************************************************
  *                                  _   _ ____  _     
  *  Project                     ___| | | |  _ \| |    
  *                             / __| | | | |_) | |    
  *                            | (__| |_| |  _ <| |___ 
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 2002, Daniel Stenberg, <daniel@haxx.se>, et al.
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
 
@@ -62,18 +62,18 @@
 /* returns last node in linked list */
 static struct curl_slist *slist_get_last(struct curl_slist *list)
 {
-        struct curl_slist       *item;
-
-        /* if caller passed us a NULL, return now */
-        if (!list)
-                return NULL;
-
-        /* loop through to find the last item */
-        item = list;
-        while (item->next) {
-                item = item->next;
-        }
-        return item;
+  struct curl_slist     *item;
+
+  /* if caller passed us a NULL, return now */
+  if (!list)
+    return NULL;
+
+  /* loop through to find the last item */
+  item = list;
+  while (item->next) {
+    item = item->next;
+  }
+  return item;
 }
 
 /* append a struct to the linked list. It always retunrs the address of the
@@ -84,61 +84,61 @@ static struct curl_slist *slist_get_last(struct curl_slist *list)
 struct curl_slist *curl_slist_append(struct curl_slist *list,
                                      const char *data)
 {
-        struct curl_slist       *last;
-        struct curl_slist       *new_item;
-
-        new_item = (struct curl_slist *) malloc(sizeof(struct curl_slist));
-        if (new_item) {
-                new_item->next = NULL;
-                new_item->data = strdup(data);
-        }
-        else {
-                fprintf(stderr, "Cannot allocate memory for QUOTE list.\n");
-                return NULL;
-        }
-
-        if (list) {
-                last = slist_get_last(list);
-                last->next = new_item;
-                return list;
-        }
-
-        /* if this is the first item, then new_item *is* the list */
-        return new_item;
+  struct curl_slist     *last;
+  struct curl_slist     *new_item;
+
+  new_item = (struct curl_slist *) malloc(sizeof(struct curl_slist));
+  if (new_item) {
+    new_item->next = NULL;
+    new_item->data = strdup(data);
+  }
+  if (new_item == NULL || new_item->data == NULL) {
+    fprintf(stderr, "Cannot allocate memory for QUOTE list.\n");
+    return NULL;
+  }
+
+  if (list) {
+    last = slist_get_last(list);
+    last->next = new_item;
+    return list;
+  }
+
+  /* if this is the first item, then new_item *is* the list */
+  return new_item;
 }
 
 /* be nice and clean up resources */
 void curl_slist_free_all(struct curl_slist *list)
 {
-        struct curl_slist       *next;
-        struct curl_slist       *item;
+  struct curl_slist     *next;
+  struct curl_slist     *item;
 
-        if (!list)
-                return;
+  if (!list)
+    return;
 
-        item = list;
-        do {
-                next = item->next;
+  item = list;
+  do {
+    next = item->next;
                 
-                if (item->data) {
-                        free(item->data);
-                }
-                free(item);
-                item = next;
-        } while (next);
+    if (item->data) {
+      free(item->data);
+    }
+    free(item);
+    item = next;
+  } while (next);
 }
 
-
 /* Curl_infof() is for info message along the way */
 
 void Curl_infof(struct SessionHandle *data, const char *fmt, ...)
 {
   va_list ap;
   if(data->set.verbose) {
+    char print_buffer[1024 + 1];
     va_start(ap, fmt);
-    fputs("* ", data->set.err);
-    vfprintf(data->set.err, fmt, ap);
+    vsnprintf(print_buffer, 1024, fmt, ap);
     va_end(ap);
+    Curl_debug(data, CURLINFO_TEXT, print_buffer, strlen(print_buffer));
   }
 }
 
@@ -153,6 +153,10 @@ void Curl_failf(struct SessionHandle *data, const char *fmt, ...)
   if(data->set.errorbuffer && !data->state.errorbuf) {
     vsnprintf(data->set.errorbuffer, CURL_ERROR_SIZE, fmt, ap);
     data->state.errorbuf = TRUE; /* wrote error string */
+
+    if(data->set.verbose)
+      Curl_debug(data, CURLINFO_TEXT, data->set.errorbuffer,
+                 strlen(data->set.errorbuffer));
   }
   va_end(ap);
 }
@@ -163,23 +167,45 @@ CURLcode Curl_sendf(int sockfd, struct connectdata *conn,
 {
   struct SessionHandle *data = conn->data;
   ssize_t bytes_written;
-  CURLcode result;
+  ssize_t write_len;
+  CURLcode res;
   char *s;
+  char *sptr;
   va_list ap;
   va_start(ap, fmt);
   s = vaprintf(fmt, ap); /* returns an allocated string */
   va_end(ap);
   if(!s)
-    return 0; /* failure */
-  if(data->set.verbose)
-    fprintf(data->set.err, "> %s", s);
+    return CURLE_OUT_OF_MEMORY; /* failure */
 
-  /* Write the buffer to the socket */
-  result = Curl_write(conn, sockfd, s, strlen(s), &bytes_written);
+  bytes_written=0;
+  write_len = strlen(s);
+  sptr = s;
+
+  do {
+    /* Write the buffer to the socket */
+    res = Curl_write(conn, sockfd, sptr, write_len, &bytes_written);
+
+    if(CURLE_OK != res)
+      break;
+
+    if(data->set.verbose)
+      Curl_debug(data, CURLINFO_DATA_OUT, sptr, bytes_written);
+
+    if(bytes_written != write_len) {
+      /* if not all was written at once, we must advance the pointer, decrease
+         the size left and try again! */
+      write_len -= bytes_written;
+      sptr += bytes_written;
+    }
+    else
+      break;
+
+  } while(1);
 
   free(s); /* free the output string */
 
-  return result;
+  return res;
 }
 
 /*
@@ -212,7 +238,7 @@ CURLcode Curl_write(struct connectdata *conn, int sockfd,
       }
       /* a true error */
       failf(conn->data, "SSL_write() return error %d\n", err);
-      return CURLE_WRITE_ERROR;
+      return CURLE_SEND_ERROR;
     }
     bytes_written = rc;
   }
@@ -244,7 +270,7 @@ CURLcode Curl_write(struct connectdata *conn, int sockfd,
 #endif
 
   *written = bytes_written;
-  return (-1 != bytes_written)?CURLE_OK:CURLE_WRITE_ERROR;
+  return (-1 != bytes_written)?CURLE_OK:CURLE_SEND_ERROR;
 }
 
 /* client_write() sends data to the write callback(s)
@@ -325,6 +351,9 @@ int Curl_read(struct connectdata *conn,
       case SSL_ERROR_WANT_WRITE:
         /* if there's data pending, then we re-invoke SSL_read() */
         break;
+      default:
+        failf(conn->data, "SSL read error: %d", err);
+        return CURLE_RECV_ERROR;
       }
     } while(loop);
     if(loop && SSL_pending(conn->ssl.handle))
@@ -355,6 +384,29 @@ int Curl_read(struct connectdata *conn,
   return CURLE_OK;
 }
 
+/* return 0 on success */
+int Curl_debug(struct SessionHandle *data, curl_infotype type,
+               char *ptr, size_t size)
+{
+  static const char * const s_infotype[CURLINFO_END] = {
+    "* ", "< ", "> ", "{ ", "} " };
+
+  if(data->set.fdebug)
+    return (*data->set.fdebug)(data, type, ptr, size,
+                               data->set.debugdata);
+
+  switch(type) {
+  case CURLINFO_TEXT:
+  case CURLINFO_HEADER_OUT:
+    fwrite(s_infotype[type], 2, 1, data->set.err);
+    fwrite(ptr, size, 1, data->set.err);
+    break;
+  default: /* nada */
+    break;
+  }
+  return 0;
+}
+
 
 /*
  * local variables: