@@ -91,7 +91,7 @@
 
 #ifdef USE_WINSOCK
 typedef FARPROC WSOCK2_FUNC;
-static CURLcode check_wsock2 (struct Curl_easy *data);
+static CURLcode check_wsock2(struct Curl_easy *data);
 #endif
 
 static
@@ -935,7 +935,7 @@ static void suboption(struct connectdata *conn)
   struct TELNET *tn = (struct TELNET *)data->req.protop;
 
   printsub(data, '<', (unsigned char *)tn->subbuffer, CURL_SB_LEN(tn)+2);
-  switch (CURL_SB_GET(tn)) {
+  switch(CURL_SB_GET(tn)) {
     case CURL_TELOPT_TTYPE:
       len = strlen(tn->subopt_ttype) + 4 + 2;
       snprintf((char *)temp, sizeof(temp),
@@ -1004,12 +1004,12 @@ static void sendsuboption(struct connectdata *conn, int option)
   ssize_t bytes_written;
   int err;
   unsigned short x, y;
-  unsigned char*uc1, *uc2;
+  unsigned char *uc1, *uc2;
 
   struct Curl_easy *data = conn->data;
   struct TELNET *tn = (struct TELNET *)data->req.protop;
 
-  switch (option) {
+  switch(option) {
   case CURL_TELOPT_NAWS:
     /* We prepare data to be sent */
     CURL_SB_CLEAR(tn);
@@ -1020,8 +1020,8 @@ static void sendsuboption(struct connectdata *conn, int option)
     /* Window size must be sent according to the 'network order' */
     x=htons(tn->subopt_wsx);
     y=htons(tn->subopt_wsy);
-    uc1 = (unsigned char*)&x;
-    uc2 = (unsigned char*)&y;
+    uc1 = (unsigned char *)&x;
+    uc2 = (unsigned char *)&y;
     CURL_SB_ACCUM(tn, uc1[0]);
     CURL_SB_ACCUM(tn, uc1[1]);
     CURL_SB_ACCUM(tn, uc2[0]);
@@ -1087,7 +1087,7 @@ CURLcode telrcv(struct connectdata *conn,
   while(count--) {
     c = inbuf[in];
 
-    switch (tn->telrcv_state) {
+    switch(tn->telrcv_state) {
     case CURL_TS_CR:
       tn->telrcv_state = CURL_TS_DATA;
       if(c == '\0') {
@@ -1111,7 +1111,7 @@ CURLcode telrcv(struct connectdata *conn,
     case CURL_TS_IAC:
     process_iac:
       DEBUGASSERT(startwrite < 0);
-      switch (c) {
+      switch(c) {
       case CURL_WILL:
         tn->telrcv_state = CURL_TS_WILL;
         break;
@@ -1241,7 +1241,7 @@ static CURLcode send_telnet_data(struct connectdata *conn,
       struct pollfd pfd[1];
       pfd[0].fd = conn->sock[FIRSTSOCKET];
       pfd[0].events = POLLOUT;
-      switch (Curl_poll(pfd, 1, -1)) {
+      switch(Curl_poll(pfd, 1, -1)) {
         case -1:                    /* error, abort writing */
         case 0:                     /* timeout (will never happen) */
           result = CURLE_SEND_ERROR;
@@ -1489,7 +1489,8 @@ static CURLcode telnet_do(struct connectdata *conn, bool *done)
 
       events.lNetworkEvents = 0;
       if(SOCKET_ERROR == enum_netevents_func(sockfd, event_handle, &events)) {
-        if((err = SOCKERRNO) != EINPROGRESS) {
+        err = SOCKERRNO;
+        if(err != EINPROGRESS) {
           infof(data, "WSAEnumNetworkEvents failed (%d)", err);
           keepon = FALSE;
           result = CURLE_READ_ERROR;
@@ -1576,7 +1577,7 @@ static CURLcode telnet_do(struct connectdata *conn, bool *done)
   }
 
   while(keepon) {
-    switch (Curl_poll(pfd, poll_cnt, interval_ms)) {
+    switch(Curl_poll(pfd, poll_cnt, interval_ms)) {
     case -1:                    /* error, stop reading */
       keepon = FALSE;
       continue;