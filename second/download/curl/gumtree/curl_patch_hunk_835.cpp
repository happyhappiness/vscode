 
   if(!netrcfile) {
     bool home_alloc = FALSE;
     char *home = curl_getenv("HOME"); /* portable environment reader */
     if(home) {
       home_alloc = TRUE;
-#if defined(HAVE_GETPWUID) && defined(HAVE_GETEUID)
+#if defined(HAVE_GETPWUID_R) && defined(HAVE_GETEUID)
+    }
+    else {
+      struct passwd pw, *pw_res;
+      char pwbuf[1024];
+      if(!getpwuid_r(geteuid(), &pw, pwbuf, sizeof(pwbuf), &pw_res)
+         && pw_res) {
+        home = strdup(pw.pw_dir);
+        if(!home)
+          return CURLE_OUT_OF_MEMORY;
+        home_alloc = TRUE;
+      }
+#elif defined(HAVE_GETPWUID) && defined(HAVE_GETEUID)
     }
     else {
       struct passwd *pw;
       pw= getpwuid(geteuid());
       if(pw) {
         home = pw->pw_dir;
       }
 #endif
     }
 
     if(!home)
-      return -1;
+      return retcode; /* no home directory found (or possibly out of memory) */
 
     netrcfile = curl_maprintf("%s%s%s", home, DIR_CHAR, NETRC);
     if(home_alloc)
       Curl_safefree(home);
     if(!netrcfile) {
       return -1;
