@@ -36,9 +36,15 @@
 #include <errno.h>
 
 #if defined(WIN32) && !defined(__GNUC__) || defined(__MINGW32__)
+#ifdef _MSC_VER
+#pragma warning (push,1)
+#endif
 #include <winsock2.h>
 #include <time.h>
 #include <io.h>
+#ifdef _MSC_VER
+#pragma warning (pop)
+#endif
 #else
 #ifdef HAVE_SYS_SOCKET_H
 #include <sys/socket.h>
@@ -260,10 +266,10 @@ static void send_negotiation(struct connectdata *conn, int cmd, int option)
    unsigned char buf[3];
 
    buf[0] = IAC;
-   buf[1] = cmd;
-   buf[2] = option;
+   buf[1] = (unsigned char)cmd;
+   buf[2] = (unsigned char)option;
    
-   swrite(conn->firstsocket, buf, 3);
+   swrite(conn->firstsocket, (char*)buf, 3);
    
    printoption(conn->data, "SENT", cmd, option);
 }
@@ -821,21 +827,21 @@ static void suboption(struct connectdata *conn)
   struct TELNET *tn = (struct TELNET *)conn->proto.telnet;
 
   printsub(data, '<', (unsigned char *)tn->subbuffer, SB_LEN(tn)+2);
-  switch (subchar = SB_GET(tn)) {
+  switch (subchar = (unsigned char)SB_GET(tn)) {
     case TELOPT_TTYPE:
       len = strlen(tn->subopt_ttype) + 4 + 2;
       snprintf((char *)temp, sizeof(temp),
                "%c%c%c%c%s%c%c", IAC, SB, TELOPT_TTYPE,
                TELQUAL_IS, tn->subopt_ttype, IAC, SE);
-      swrite(conn->firstsocket, temp, len);
+      swrite(conn->firstsocket, (char*)temp, len);
       printsub(data, '>', &temp[2], len-2);
       break;
     case TELOPT_XDISPLOC:
       len = strlen(tn->subopt_xdisploc) + 4 + 2;
       snprintf((char *)temp, sizeof(temp),
                "%c%c%c%c%s%c%c", IAC, SB, TELOPT_XDISPLOC,
                TELQUAL_IS, tn->subopt_xdisploc, IAC, SE);
-      swrite(conn->firstsocket, temp, len);
+      swrite(conn->firstsocket, (char*)temp, len);
       printsub(data, '>', &temp[2], len-2);
       break;
     case TELOPT_NEW_ENVIRON:
@@ -857,7 +863,7 @@ static void suboption(struct connectdata *conn)
       snprintf((char *)&temp[len], sizeof(temp) - len,
                "%c%c", IAC, SE);
       len += 2;
-      swrite(conn->firstsocket, temp, len);
+      swrite(conn->firstsocket, (char*)temp, len);
       printsub(data, '>', &temp[2], len-2);
       break;
   }
@@ -1051,6 +1057,7 @@ CURLcode Curl_telnet(struct connectdata *conn)
   ssize_t nread;
   struct TELNET *tn;
   struct timeval now;           /* current time */
+  (void) now;
 
   code = init_telnet(conn);
   if(code)
@@ -1095,7 +1102,7 @@ CURLcode Curl_telnet(struct connectdata *conn)
         ssize_t bytes_written;
         char *buffer = buf;
               
-        if(!ReadFile(stdin_handle, buf, 255, &nread, NULL)) {
+        if(!ReadFile(stdin_handle, buf, 255, &(DWORD)nread, NULL)) {
           keepon = FALSE;
           break;
         }