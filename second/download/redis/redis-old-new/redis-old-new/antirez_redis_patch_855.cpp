@@ -304,11 +304,21 @@ void redisLogRaw(int level, const char *msg) {
     } else {
         int off;
         struct timeval tv;
+        int role_char;
+        pid_t pid = getpid();
 
         gettimeofday(&tv,NULL);
         off = strftime(buf,sizeof(buf),"%d %b %H:%M:%S.",localtime(&tv.tv_sec));
         snprintf(buf+off,sizeof(buf)-off,"%03d",(int)tv.tv_usec/1000);
-        fprintf(fp,"[%d] %s %c %s\n",(int)getpid(),buf,c[level],msg);
+        if (server.sentinel_mode) {
+            role_char = 'X'; /* Sentinel. */
+        } else if (pid != server.pid) {
+            role_char = 'C'; /* RDB / AOF writing child. */
+        } else {
+            role_char = (server.masterhost ? 'S':'M'); /* Slave or Master. */
+        }
+        fprintf(fp,"%d:%c %s %c %s\n",
+            (int)getpid(),role_char, buf,c[level],msg);
     }
     fflush(fp);
 
@@ -1687,6 +1697,7 @@ void initServer() {
             server.syslog_facility);
     }
 
+    server.pid = getpid();
     server.current_client = NULL;
     server.clients = listCreate();
     server.clients_to_close = listCreate();