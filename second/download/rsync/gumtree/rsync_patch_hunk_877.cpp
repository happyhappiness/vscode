 		if (rerr_names[i].code == code)
 			return rerr_names[i].name;
 	}
 	return NULL;
 }
 
-static void logit(int priority, char *buf)
+static void logit(int priority, const char *buf)
 {
 	if (logfile_was_closed)
 		logfile_reopen();
 	if (logfile_fp) {
 		fprintf(logfile_fp, "%s [%d] %s",
 			timestring(time(NULL)), (int)getpid(), buf);
