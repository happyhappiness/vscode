         return -1;
     if ((a->waittime) > (b->waittime))
         return 1;
     return 0;
 }
 
-static void output_results(void)
+static void output_results(int sig)
 {
-    apr_interval_time_t timetakenusec;
-    float timetaken;
+    double timetaken;
 
-    endtime = apr_time_now();
-    timetakenusec = endtime - start;
-    timetaken = ((float)apr_time_sec(timetakenusec)) +
-        ((float)apr_time_usec(timetakenusec)) / 1000000.0F;
+    if (sig) {
+        lasttime = apr_time_now();  /* record final time if interrupted */
+    }
+    timetaken = (double) (lasttime - start) / APR_USEC_PER_SEC;
 
     printf("\n\n");
     printf("Server Software:        %s\n", servername);
     printf("Server Hostname:        %s\n", hostname);
     printf("Server Port:            %hu\n", port);
 #ifdef USE_SSL
