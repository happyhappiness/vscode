         /* LF -> CRLF conversion? */
         config->crlf = toggle;
         break;
 
       case 'v': /* --stderr */
         if(strcmp(nextarg, "-")) {
-          FILE *newfile = fopen(nextarg, "wt");
+          FILE *newfile = fopen(nextarg, FOPEN_WRITETEXT);
           if(!newfile)
             warnf(global, "Failed to open %s!\n", nextarg);
           else {
             if(global->errors_fopened)
               fclose(global->errors);
             global->errors = newfile;
