 }
 
 static void logit(int priority, char *buf)
 {
 	if (logfile_was_closed)
 		logfile_reopen();
-	if (logfile) {
-		fprintf(logfile,"%s [%d] %s",
+	if (logfile_fp) {
+		fprintf(logfile_fp, "%s [%d] %s",
 			timestring(time(NULL)), (int)getpid(), buf);
-		fflush(logfile);
+		fflush(logfile_fp);
 	} else {
 		syslog(priority, "%s", buf);
 	}
 }
 
 static void syslog_init()
