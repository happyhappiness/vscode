       if(-1 == (int)config->condtime) {
         /* now let's see if it is a file name to get the time from instead! */
         struct_stat statbuf;
         if(-1 == stat(nextarg, &statbuf)) {
           /* failed, remove time condition */
           config->timecond = CURL_TIMECOND_NONE;
-          fprintf(stderr,
-                  "Warning: Illegal date format for -z/--timecond and not "
-                  "a file name.\n"
-                  "         See curl_getdate(3) for valid date syntax.\n");
+          warnf(config,
+                "Illegal date format for -z/--timecond (and not "
+                "a file name). Disabling time condition. "
+                "See curl_getdate(3) for valid date syntax.\n");
         }
         else {
           /* pull the time out from the file */
           config->condtime = statbuf.st_mtime;
         }
       }
