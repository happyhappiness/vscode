@@ -252,18 +252,17 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
         return 1;
     }
 
+    /* Build the command to send */
+    cmd = sdscatprintf(sdsempty(),"*%d\r\n",argc);
+    for (j = 0; j < argc; j++) {
+        cmd = sdscatprintf(cmd,"$%lu\r\n",
+            (unsigned long)sdslen(argv[j]));
+        cmd = sdscatlen(cmd,argv[j],sdslen(argv[j]));
+        cmd = sdscatlen(cmd,"\r\n",2);
+    }
+
     while(repeat--) {
-        /* Build the command to send */
-        cmd = sdscatprintf(sdsempty(),"*%d\r\n",argc);
-        for (j = 0; j < argc; j++) {
-            cmd = sdscatprintf(cmd,"$%lu\r\n",
-                (unsigned long)sdslen(argv[j]));
-            cmd = sdscatlen(cmd,argv[j],sdslen(argv[j]));
-            cmd = sdscatlen(cmd,"\r\n",2);
-        }
         anetWrite(fd,cmd,sdslen(cmd));
-        sdsfree(cmd);
-
         while (config.monitor_mode) {
             cliReadSingleLineReply(fd,0);
         }
@@ -277,7 +276,6 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
         }
 
         retval = cliReadReply(fd);
-
         if (retval) {
             return retval;
         }