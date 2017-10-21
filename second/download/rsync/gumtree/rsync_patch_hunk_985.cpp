 
 static void logit(int priority, const char *buf)
 {
 	if (logfile_was_closed)
 		logfile_reopen();
 	if (logfile_fp) {
-		fprintf(logfile_fp, "%s [%d] %s",
-			timestring(time(NULL)), (int)getpid(), buf);
+		fprintf(logfile_fp, "%s [%d] %s", timestring(time(NULL)), (int)getpid(), buf);
 		fflush(logfile_fp);
 	} else {
 		syslog(priority, "%s", buf);
 	}
 }
 
