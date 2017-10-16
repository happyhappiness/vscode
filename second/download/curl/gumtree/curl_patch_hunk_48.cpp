 };
 
 /* make sure we have room for at least this size: */
 #define LOGINSIZE 64
 #define PASSWORDSIZE 64
 
+/* returns -1 on failure, 0 if the host is found, 1 is the host isn't found */
 int Curl_parsenetrc(char *host,
                     char *login,
-                    char *password)
+                    char *password,
+                    char *netrcfile)
 {
   FILE *file;
-  char netrcbuffer[256];
   int retcode=1;
-
   int specific_login = (login[0] != 0);
-  
   char *home = NULL; 
+  bool home_alloc = FALSE;
+  bool netrc_alloc = FALSE;
   int state=NOTHING;
 
   char state_login=0;      /* Found a login keyword */
   char state_password=0;   /* Found a password keyword */
   char state_our_login=0;  /* With specific_login, found *our* login name */
 
 #define NETRC DOT_CHAR "netrc"
 
-#if defined(HAVE_GETPWUID) && defined(HAVE_GETEUID)
-  struct passwd *pw;
-  pw= getpwuid(geteuid());
-  if (pw) {
-#ifdef	VMS
-    home = decc$translate_vms(pw->pw_dir);
-#else
-    home = pw->pw_dir;
-#endif
-  }
-#else
-  void *pw=NULL;
-#endif
-  
-  if(NULL == pw) {
-    home = curl_getenv("HOME"); /* portable environment reader */
-    if(!home) {
-      return -1;
-    }
-  }
-
-  if(strlen(home)>(sizeof(netrcbuffer)-strlen(NETRC))) {
-    if(NULL==pw)
-      free(home);
-    return -1;
-  }
-
-  sprintf(netrcbuffer, "%s%s%s", home, DIR_CHAR, NETRC);
-
 #ifdef CURLDEBUG
   {
     /* This is a hack to allow testing.
      * If compiled with --enable-debug and CURL_DEBUG_NETRC is defined,
      * then it's the path to a substitute .netrc for testing purposes *only* */
 
     char *override = curl_getenv("CURL_DEBUG_NETRC");
 
-    if (override != NULL) {
-      printf("NETRC: overridden .netrc file: %s\n", home);
-
-      if (strlen(override)+1 > sizeof(netrcbuffer)) {
-        free(override);
-        if(NULL==pw)
-          free(home);
-
-        return -1;
-      }
-      strcpy(netrcbuffer, override);
-      free(override);
+    if (override) {
+      printf("NETRC: overridden " NETRC " file: %s\n", home);
+      netrcfile = override;
+      netrc_alloc = TRUE;
     }
   }
 #endif /* CURLDEBUG */
+  if(!netrcfile) {
+#if defined(HAVE_GETPWUID) && defined(HAVE_GETEUID)
+    struct passwd *pw;
+    pw= getpwuid(geteuid());
+    if (pw) {
+#ifdef	VMS
+      home = decc$translate_vms(pw->pw_dir);
+#else
+      home = pw->pw_dir;
+#endif
+    }
+#endif
+  
+    if(!home) {
+      home = curl_getenv("HOME"); /* portable environment reader */
+      if(!home)
+        return -1;
+      home_alloc = TRUE;
+    }
+
+    netrcfile = curl_maprintf("%s%s%s", home, DIR_CHAR, NETRC);
+    if(!netrcfile) {
+      if(home_alloc)
+        free(home);
+      return -1;
+    }
+    netrc_alloc = TRUE;
+  }
 
-  file = fopen(netrcbuffer, "r");
+  file = fopen(netrcfile, "r");
   if(file) {
     char *tok;
     char *tok_buf;
     bool done=FALSE;
+    char netrcbuffer[256];
 
     while(!done && fgets(netrcbuffer, sizeof(netrcbuffer), file)) {
       tok=strtok_r(netrcbuffer, " \t\n", &tok_buf);
       while(!done && tok) {
 
         if (login[0] && password[0]) {
