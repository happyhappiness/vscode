@@ -55,9 +55,10 @@
 #include "sockaddr.h" /* required for Curl_sockaddr_storage */
 #include "multiif.h"
 #include "url.h"
-#include "rawstr.h"
+#include "strcase.h"
 #include "speedcheck.h"
 #include "select.h"
+#include "escape.h"
 
 /* The last 3 #include files should be in this order */
 #include "curl_printf.h"
@@ -484,10 +485,10 @@ static CURLcode tftp_send_first(tftp_state_data_t *state, tftp_event_t event)
     /* As RFC3617 describes the separator slash is not actually part of the
        file name so we skip the always-present first letter of the path
        string. */
-    filename = curl_easy_unescape(data, &state->conn->data->state.path[1], 0,
-                                  NULL);
-    if(!filename)
-      return CURLE_OUT_OF_MEMORY;
+    result = Curl_urldecode(data, &state->conn->data->state.path[1], 0,
+                            &filename, NULL, FALSE);
+    if(result)
+      return result;
 
     snprintf((char *)state->spacket.data+2,
              state->blksize,
@@ -705,6 +706,7 @@ static CURLcode tftp_tx(tftp_state_data_t *state, tftp_event_t event)
   int rblock;
   CURLcode result = CURLE_OK;
   struct SingleRequest *k = &data->req;
+  int cb; /* Bytes currently read */
 
   switch(event) {
 
@@ -762,9 +764,20 @@ static CURLcode tftp_tx(tftp_state_data_t *state, tftp_event_t event)
       return CURLE_OK;
     }
 
-    result = Curl_fillreadbuffer(state->conn, state->blksize, &state->sbytes);
-    if(result)
-      return result;
+    /* TFTP considers data block size < 512 bytes as an end of session. So
+     * in some cases we must wait for additional data to build full (512 bytes)
+     * data block.
+     * */
+    state->sbytes = 0;
+    state->conn->data->req.upload_fromhere = (char *)state->spacket.data+4;
+    do {
+      result = Curl_fillreadbuffer(state->conn, state->blksize - state->sbytes,
+                                   &cb);
+      if(result)
+        return result;
+      state->sbytes += cb;
+      state->conn->data->req.upload_fromhere += cb;
+    } while(state->sbytes < state->blksize && cb != 0);
 
     sbytes = sendto(state->sockfd, (void *) state->spacket.data,
                     4 + state->sbytes, SEND_4TH_ARG,
@@ -1221,7 +1234,7 @@ static CURLcode tftp_multi_statemach(struct connectdata *conn, bool *done)
   }
   else {
     /* no timeouts to handle, check our socket */
-    rc = Curl_socket_ready(state->sockfd, CURL_SOCKET_BAD, 0);
+    rc = SOCKET_READABLE(state->sockfd, 0);
 
     if(rc == -1) {
       /* bail out */