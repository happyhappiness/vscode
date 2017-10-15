   {
     fprintf(stderr, "%s: I don't want to run with privileges!\n",
 	    argv[0]);
     exit(1);
   }
 
+  setlocale (LC_ALL, "");
+
 #ifdef ENABLE_NLS
   /* FIXME what about init.c:1439 ? */
-  setlocale (LC_ALL, "");
   bindtextdomain (PACKAGE, MUTTLOCALEDIR);
   textdomain (PACKAGE);
 #endif
 
-  setlocale (LC_CTYPE, "");
-
   mutt_error = mutt_nocurses_error;
   mutt_message = mutt_nocurses_error;
   SRAND (time (NULL));
   umask (077);
 
   memset (Options, 0, sizeof (Options));
   memset (QuadOptions, 0, sizeof (QuadOptions));
 
+  /* Init envlist */
+  {
+    char **srcp, **dstp;
+    int count = 0;
+    for (srcp = environ; srcp && *srcp; srcp++)
+      count++;
+    envlist = safe_calloc(count+1, sizeof(char *));
+    for (srcp = environ, dstp = envlist; srcp && *srcp; srcp++, dstp++)
+      *dstp = safe_strdup(*srcp);
+  }
+
   for (optind = 1; optind < double_dash; )
   {
     /* We're getopt'ing POSIXLY, so we'll be here every time getopt()
      * encounters a non-option.  That could be a file to attach 
      * (all non-options between -a and --) or it could be an address
      * (which gets collapsed to the front of argv).
