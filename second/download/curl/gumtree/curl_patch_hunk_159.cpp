         /* LF -> CRLF conversinon? */
         config->crlf = TRUE;
         break;
 
       case 'v': /* --stderr */
         if(strcmp(nextarg, "-")) {
-          config->errors = fopen(nextarg, "wt");
-          config->errors_fopened = TRUE;
+          FILE *newfile = fopen(nextarg, "wt");
+          if(!config->errors)
+            warnf(config, "Failed to open %s!\n", nextarg);
+          else {
+            config->errors = newfile;
+            config->errors_fopened = TRUE;
+          }
         }
         else
           config->errors = stdout;
       break;
       case 'w': /* --interface */
         /* interface */
