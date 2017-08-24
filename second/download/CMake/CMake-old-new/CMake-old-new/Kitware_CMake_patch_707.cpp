@@ -884,7 +884,7 @@ ftp_pasv_verbose(struct connectdata *conn,
   int h_errnop;
 # endif
   char *hostent_buf = (char *)bigbuf; /* get a char * to the buffer */
-
+  (void)hostent_buf;
   address = inet_addr(newhost);
 # ifdef HAVE_GETHOSTBYADDR_R
 
@@ -1434,7 +1434,7 @@ CURLcode ftp_use_pasv(struct connectdata *conn,
 
     sprintf(newhost, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
     newhostp = newhost;
-    newport = (port[0]<<8) + port[1];
+    newport = (unsigned short)((port[0]<<8) + port[1]);
   }
 #if 1
   else if (229 == results[modeoff]) {
@@ -1450,7 +1450,7 @@ CURLcode ftp_use_pasv(struct connectdata *conn,
                       &num,
                       &separator[3])) {
         /* the four separators should be identical */
-        newport = num;
+        newport = (unsigned short)num;
 
         /* we should use the same host we already are connected to */
         newhostp = conn->name;
@@ -2003,7 +2003,7 @@ CURLcode ftp_perform(struct connectdata *conn,
       struct tm buffer;
       tm = (struct tm *)localtime_r(&data->info.filetime, &buffer);
 #else
-      tm = localtime((unsigned long *)&data->info.filetime);
+      tm = localtime((time_t *)&data->info.filetime);
 #endif
       /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
       strftime(buf, BUFSIZE-1, "Last-Modified: %a, %d %b %Y %H:%M:%S %Z\r\n",