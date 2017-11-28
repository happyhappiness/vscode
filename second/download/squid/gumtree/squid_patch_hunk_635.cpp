     if (stat(argv[1], &sb) != 0) {
         fprintf(stderr, "FATAL: cannot stat %s\n", argv[1]);
         exit(1);
     }
     while (fgets(buf, HELPER_INPUT_BUFFER, stdin) != NULL) {
         if ((p = strchr(buf, '\n')) != NULL)
-            *p = '\0';		/* strip \n */
+            *p = '\0';      /* strip \n */
         if (stat(argv[1], &sb) == 0) {
             if (sb.st_mtime != change_time) {
                 read_passwd_file(argv[1]);
                 change_time = sb.st_mtime;
             }
         }
