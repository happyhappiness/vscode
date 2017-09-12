@@ -1441,7 +1441,7 @@ void createPidFile(void) {
     /* Try to write the pid file in a best-effort way. */
     FILE *fp = fopen(server.pidfile,"w");
     if (fp) {
-        fprintf(fp,"%d\n",getpid());
+        fprintf(fp,"%d\n",(int)getpid());
         fclose(fp);
     }
 }