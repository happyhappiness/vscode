@@ -5,11 +5,11 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
- * are also available at http://curl.haxx.se/docs/copyright.html.
+ * are also available at https://curl.haxx.se/docs/copyright.html.
  *
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
@@ -57,10 +57,10 @@
 #include "url.h"
 #include "rawstr.h"
 #include "speedcheck.h"
-#include "curl_printf.h"
 #include "select.h"
 
-/* The last #include files should be: */
+/* The last 3 #include files should be in this order */
+#include "curl_printf.h"
 #include "curl_memory.h"
 #include "memdebug.h"
 
@@ -312,14 +312,14 @@ static const char *tftp_option_get(const char *buf, size_t len,
 {
   size_t loc;
 
-  loc = Curl_strnlen( buf, len );
+  loc = Curl_strnlen(buf, len);
   loc++; /* NULL term */
 
   if(loc >= len)
     return NULL;
   *option = buf;
 
-  loc += Curl_strnlen( buf+loc, len-loc );
+  loc += Curl_strnlen(buf+loc, len-loc);
   loc++; /* NULL term */
 
   if(loc > len)
@@ -333,7 +333,7 @@ static CURLcode tftp_parse_option_ack(tftp_state_data_t *state,
                                       const char *ptr, int len)
 {
   const char *tmp = ptr;
-  struct SessionHandle *data = state->conn->data;
+  struct Curl_easy *data = state->conn->data;
 
   /* if OACK doesn't contain blksize option, the default (512) must be used */
   state->blksize = TFTP_BLKSIZE_DEFAULT;
@@ -352,7 +352,7 @@ static CURLcode tftp_parse_option_ack(tftp_state_data_t *state,
     if(checkprefix(option, TFTP_OPTION_BLKSIZE)) {
       long blksize;
 
-      blksize = strtol( value, NULL, 10 );
+      blksize = strtol(value, NULL, 10);
 
       if(!blksize) {
         failf(data, "invalid blocksize value in OACK packet");
@@ -384,7 +384,7 @@ static CURLcode tftp_parse_option_ack(tftp_state_data_t *state,
     else if(checkprefix(option, TFTP_OPTION_TSIZE)) {
       long tsize = 0;
 
-      tsize = strtol( value, NULL, 10 );
+      tsize = strtol(value, NULL, 10);
       infof(data, "%s (%ld)\n", "tsize parsed from OACK", tsize);
 
       /* tsize should be ignored on upload: Who cares about the size of the
@@ -405,7 +405,7 @@ static CURLcode tftp_parse_option_ack(tftp_state_data_t *state,
 static size_t tftp_option_add(tftp_state_data_t *state, size_t csize,
                               char *buf, const char *option)
 {
-  if(( strlen(option) + csize + 1 ) > (size_t)state->blksize)
+  if(( strlen(option) + csize + 1) > (size_t)state->blksize)
     return 0;
   strcpy(buf, option);
   return strlen(option) + 1;
@@ -416,7 +416,7 @@ static CURLcode tftp_connect_for_tx(tftp_state_data_t *state,
 {
   CURLcode result;
 #ifndef CURL_DISABLE_VERBOSE_STRINGS
-  struct SessionHandle *data = state->conn->data;
+  struct Curl_easy *data = state->conn->data;
 
   infof(data, "%s\n", "Connected for transmit");
 #endif
@@ -432,7 +432,7 @@ static CURLcode tftp_connect_for_rx(tftp_state_data_t *state,
 {
   CURLcode result;
 #ifndef CURL_DISABLE_VERBOSE_STRINGS
-  struct SessionHandle *data = state->conn->data;
+  struct Curl_easy *data = state->conn->data;
 
   infof(data, "%s\n", "Connected for receive");
 #endif
@@ -450,7 +450,7 @@ static CURLcode tftp_send_first(tftp_state_data_t *state, tftp_event_t event)
   const char *mode = "octet";
   char *filename;
   char buf[64];
-  struct SessionHandle *data = state->conn->data;
+  struct Curl_easy *data = state->conn->data;
   CURLcode result = CURLE_OK;
 
   /* Set ascii mode if -B flag was used */
@@ -494,33 +494,36 @@ static CURLcode tftp_send_first(tftp_state_data_t *state, tftp_event_t event)
              "%s%c%s%c", filename, '\0',  mode, '\0');
     sbytes = 4 + strlen(filename) + strlen(mode);
 
-    /* add tsize option */
-    if(data->set.upload && (data->state.infilesize != -1))
-      snprintf(buf, sizeof(buf), "%" CURL_FORMAT_CURL_OFF_T,
-               data->state.infilesize);
-    else
-      strcpy(buf, "0"); /* the destination is large enough */
-
-    sbytes += tftp_option_add(state, sbytes,
-                              (char *)state->spacket.data+sbytes,
-                              TFTP_OPTION_TSIZE);
-    sbytes += tftp_option_add(state, sbytes,
-                              (char *)state->spacket.data+sbytes, buf);
-    /* add blksize option */
-    snprintf( buf, sizeof(buf), "%d", state->requested_blksize );
-    sbytes += tftp_option_add(state, sbytes,
-                              (char *)state->spacket.data+sbytes,
-                              TFTP_OPTION_BLKSIZE);
-    sbytes += tftp_option_add(state, sbytes,
-                              (char *)state->spacket.data+sbytes, buf );
-
-    /* add timeout option */
-    snprintf( buf, sizeof(buf), "%d", state->retry_time);
-    sbytes += tftp_option_add(state, sbytes,
-                              (char *)state->spacket.data+sbytes,
-                              TFTP_OPTION_INTERVAL);
-    sbytes += tftp_option_add(state, sbytes,
-                              (char *)state->spacket.data+sbytes, buf );
+    /* optional addition of TFTP options */
+    if(!data->set.tftp_no_options) {
+      /* add tsize option */
+      if(data->set.upload && (data->state.infilesize != -1))
+        snprintf(buf, sizeof(buf), "%" CURL_FORMAT_CURL_OFF_T,
+                 data->state.infilesize);
+      else
+        strcpy(buf, "0"); /* the destination is large enough */
+
+      sbytes += tftp_option_add(state, sbytes,
+                                (char *)state->spacket.data+sbytes,
+                                TFTP_OPTION_TSIZE);
+      sbytes += tftp_option_add(state, sbytes,
+                                (char *)state->spacket.data+sbytes, buf);
+      /* add blksize option */
+      snprintf(buf, sizeof(buf), "%d", state->requested_blksize);
+      sbytes += tftp_option_add(state, sbytes,
+                                (char *)state->spacket.data+sbytes,
+                                TFTP_OPTION_BLKSIZE);
+      sbytes += tftp_option_add(state, sbytes,
+                                (char *)state->spacket.data+sbytes, buf);
+
+      /* add timeout option */
+      snprintf(buf, sizeof(buf), "%d", state->retry_time);
+      sbytes += tftp_option_add(state, sbytes,
+                                (char *)state->spacket.data+sbytes,
+                                TFTP_OPTION_INTERVAL);
+      sbytes += tftp_option_add(state, sbytes,
+                                (char *)state->spacket.data+sbytes, buf);
+    }
 
     /* the typecase for the 3rd argument is mostly for systems that do
        not have a size_t argument, like older unixes that want an 'int' */
@@ -578,7 +581,7 @@ static CURLcode tftp_rx(tftp_state_data_t *state, tftp_event_t event)
 {
   ssize_t sbytes;
   int rblock;
-  struct SessionHandle *data = state->conn->data;
+  struct Curl_easy *data = state->conn->data;
 
   switch(event) {
 
@@ -697,7 +700,7 @@ static CURLcode tftp_rx(tftp_state_data_t *state, tftp_event_t event)
  **********************************************************/
 static CURLcode tftp_tx(tftp_state_data_t *state, tftp_event_t event)
 {
-  struct SessionHandle *data = state->conn->data;
+  struct Curl_easy *data = state->conn->data;
   ssize_t sbytes;
   int rblock;
   CURLcode result = CURLE_OK;
@@ -886,7 +889,7 @@ static CURLcode tftp_state_machine(tftp_state_data_t *state,
                                    tftp_event_t event)
 {
   CURLcode result = CURLE_OK;
-  struct SessionHandle *data = state->conn->data;
+  struct Curl_easy *data = state->conn->data;
 
   switch(state->state) {
   case TFTP_STATE_START:
@@ -957,7 +960,7 @@ static CURLcode tftp_connect(struct connectdata *conn, bool *done)
   /* alloc pkt buffers based on specified blksize */
   if(conn->data->set.tftp_blksize) {
     blksize = (int)conn->data->set.tftp_blksize;
-    if(blksize > TFTP_BLKSIZE_MAX || blksize < TFTP_BLKSIZE_MIN )
+    if(blksize > TFTP_BLKSIZE_MAX || blksize < TFTP_BLKSIZE_MIN)
       return CURLE_TFTP_ILLEGAL;
   }
 
@@ -975,7 +978,7 @@ static CURLcode tftp_connect(struct connectdata *conn, bool *done)
       return CURLE_OUT_OF_MEMORY;
   }
 
-  /* we don't keep TFTP connections up bascially because there's none or very
+  /* we don't keep TFTP connections up basically because there's none or very
    * little gain for UDP */
   connclose(conn, "TFTP");
 
@@ -1078,7 +1081,7 @@ static CURLcode tftp_receive_packet(struct connectdata *conn)
   struct Curl_sockaddr_storage fromaddr;
   curl_socklen_t        fromlen;
   CURLcode              result = CURLE_OK;
-  struct SessionHandle  *data = conn->data;
+  struct Curl_easy  *data = conn->data;
   tftp_state_data_t     *state = (tftp_state_data_t *)conn->proto.tftpc;
   struct SingleRequest  *k = &data->req;
 
@@ -1197,7 +1200,7 @@ static CURLcode tftp_multi_statemach(struct connectdata *conn, bool *done)
   int                   rc;
   tftp_event_t          event;
   CURLcode              result = CURLE_OK;
-  struct SessionHandle  *data = conn->data;
+  struct Curl_easy  *data = conn->data;
   tftp_state_data_t     *state = (tftp_state_data_t *)conn->proto.tftpc;
   long                  timeout_ms = tftp_state_timeout(conn, &event);
 
@@ -1339,7 +1342,7 @@ static CURLcode tftp_do(struct connectdata *conn, bool *done)
 
 static CURLcode tftp_setup_connection(struct connectdata * conn)
 {
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   char * type;
   char command;
 