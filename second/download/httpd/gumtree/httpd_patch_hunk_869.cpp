 
 globals allowed_globals = {NULL, NULL, NULL, NULL, 0};
 
 #define MAX_SELECT_ERRORS 100
 
 
-static void add_job(int sock)
+static void add_job(SOCKET sock)
 {
     joblist *new_job;
 
     new_job = (joblist *) malloc(sizeof(joblist));
     if (new_job == NULL) {
-	ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
+        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                      "Ouch!  Out of memory in add_job()!");
         return;
     }
     new_job->next = NULL;
     new_job->sock = sock;
 
