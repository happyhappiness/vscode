         fprintf(stderr, "Unable to initialize htdbm terminating!\n");
         apr_strerror(rv, errbuf, sizeof(errbuf));
         exit(1);
     }
     /*
      * Preliminary check to make sure they provided at least
-     * three arguments, we'll do better argument checking as 
+     * three arguments, we'll do better argument checking as
      * we parse the command line.
      */
     if (argc < 3)
        htdbm_usage();
     /*
      * Go through the argument list and pick out any options.  They
      * have to precede any other arguments.
      */
     for (i = 1; i < argc; i++) {
         arg = argv[i];
         if (*arg != '-')
             break;
-        
+
         while (*++arg != '\0') {
             switch (*arg) {
             case 'b':
                 pwd_supplied = 1;
                 need_pwd = 0;
                 args_left++;
