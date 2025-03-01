       case 'v': /* --stderr */
         if(strcmp(nextarg, "-")) {
           FILE *newfile = fopen(nextarg, "wt");
           if(!newfile)
             warnf(config, "Failed to open %s!\n", nextarg);
           else {
-            if(config->errors_fopened)
-              fclose(config->errors);
-            config->errors = newfile;
-            config->errors_fopened = TRUE;
+            if(global->errors_fopened)
+              fclose(global->errors);
+            global->errors = newfile;
+            global->errors_fopened = TRUE;
           }
         }
         else
-          config->errors = stdout;
+          global->errors = stdout;
         break;
       case 'w': /* --interface */
         /* interface */
         GetStr(&config->iface, nextarg);
         break;
       case 'x': /* --krb */
