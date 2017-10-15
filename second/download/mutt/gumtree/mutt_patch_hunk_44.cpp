     rename (buf, buf2);
   }
   if ((debugfile = safe_fopen(buf, "w")) != NULL)
   {
     t = time (0);
     setbuf (debugfile, NULL); /* don't buffer the debugging output! */
-    fprintf (debugfile, "Mutt %s started at %s.\nDebugging at level %d.\n\n",
-	     MUTT_VERSION, asctime (localtime (&t)), debuglevel);
+    dprint(1,(debugfile,"Mutt/%s (%s) debugging at level %d\n",
+	      MUTT_VERSION, ReleaseDate, debuglevel));
   }
 }
 #endif
 
 static int mutt_execute_commands (LIST *p)
 {
   BUFFER err, token;
-  char errstr[SHORT_STRING];
 
-  memset (&err, 0, sizeof (err));
-  err.data = errstr;
-  err.dsize = sizeof (errstr);
-  memset (&token, 0, sizeof (token));
+  mutt_buffer_init (&err);
+  err.dsize = STRING;
+  err.data = safe_malloc (err.dsize);
+  mutt_buffer_init (&token);
   for (; p; p = p->next)
   {
     if (mutt_parse_rc_line (p->data, &token, &err) != 0)
     {
       fprintf (stderr, _("Error in command line: %s\n"), err.data);
       FREE (&token.data);
-      return (-1);
+      FREE (&err.data);
+
+      return -1;
     }
   }
   FREE (&token.data);
+  FREE (&err.data);
+
   return 0;
 }
 
+static void mutt_srandom (void)
+{
+  struct timeval tv;
+  unsigned seed;
+
+  gettimeofday(&tv, NULL);
+  /* POSIX.1-2008 states that seed is 'unsigned' without specifying its width.
+   * Use as many of the lower order bits from the current time of day as the seed.
+   * If the upper bound is truncated, that is fine.
+   *
+   * tv_sec is integral of type integer or float.  Cast to 'long long' before
+   * bitshift in case it is a float.
+   */
+  seed = ((LONGLONG) tv.tv_sec << 20) | tv.tv_usec;
+  srandom(seed);
+}
+
 void mutt_init (int skip_sys_rc, LIST *commands)
 {
   struct passwd *pw;
   struct utsname utsname;
-  char *p, buffer[STRING], error[STRING];
+  char *p, buffer[STRING];
   int i, default_rc = 0, need_pause = 0;
   BUFFER err;
 
-  memset (&err, 0, sizeof (err));
-  err.data = error;
-  err.dsize = sizeof (error);
+  mutt_buffer_init (&err);
+  err.dsize = STRING;
+  err.data = safe_malloc(err.dsize);
+  err.dptr = err.data;
+
+  Groups = hash_create (1031, 0);
+  ReverseAlias = hash_create (1031, 1);
+  
+  mutt_menu_init ();
+  mutt_srandom ();
 
   /* 
    * XXX - use something even more difficult to predict?
    */
   snprintf (AttachmentMarker, sizeof (AttachmentMarker),
 	    "\033]9;%ld\a", (long) time (NULL));
