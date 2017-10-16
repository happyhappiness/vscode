         FILE *file;
         nextarg++; /* pass the @ */
         if(curlx_strequal("-", nextarg))
           file = stdin;
         else
           file = fopen(nextarg, "r");
-        config->writeout = file2string(file);
-        if(!config->writeout)
-          warnf(config, "Failed to read %s", file);
+        err = file2string(&config->writeout, file);
         if(file && (file != stdin))
           fclose(file);
+        if(err)
+          return err;
+        if(!config->writeout)
+          warnf(config, "Failed to read %s", file);
       }
       else
         GetStr(&config->writeout, nextarg);
       break;
     case 'x':
       /* proxy */
