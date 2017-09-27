             colon = strchr(scratch, ':');
             if (colon != NULL) {
                 *colon = '\0';
             }
             else {
                 /*
-                 * If we've not got a colon on the line, this could well 
+                 * If we've not got a colon on the line, this could well
                  * not be a valid htpasswd file.
                  * We should bail at this point.
                  */
-                apr_file_printf(errfile, "\n%s: The file %s does not appear "
-                                         "to be a valid htpasswd file.\n",
+                apr_file_printf(errfile, "%s: The file %s does not appear "
+                                         "to be a valid htpasswd file." NL,
                                 argv[0], pwfilename);
                 apr_file_close(fpw);
                 exit(ERR_INVALID);
             }
             if (strcmp(user, scratch) != 0) {
                 putline(ftemp, line);
