     }
 
     if(!home)
       return -1;
 
     netrcfile = curl_maprintf("%s%s%s", home, DIR_CHAR, NETRC);
+    if(home_alloc)
+      Curl_safefree(home);
     if(!netrcfile) {
-      if(home_alloc)
-        free(home);
       return -1;
     }
     netrc_alloc = TRUE;
   }
 
   file = fopen(netrcfile, "r");
+  if(netrc_alloc)
+    Curl_safefree(netrcfile);
   if(file) {
     char *tok;
     char *tok_buf;
     bool done=FALSE;
     char netrcbuffer[256];
     int  netrcbuffsize = (int)sizeof(netrcbuffer);
