 }
 
 /// \ingroup ErrorPageInternal
 #define CVT_BUF_SZ 512
 
 const char *
-ErrorState::Convert(char token, bool allowRecursion)
+ErrorState::Convert(char token, bool building_deny_info_url, bool allowRecursion)
 {
     static MemBuf mb;
     const char *p = NULL;	/* takes priority over mb if set */
     int do_quote = 1;
+    int no_urlescape = 0;       /* if true then item is NOT to be further URL-encoded */
     char ntoabuf[MAX_IPSTRLEN];
 
     mb.reset();
 
     switch (token) {
 
     case 'a':
-
-        if (request && request->auth_user_request)
+#if USE_AUTH
+        if (request && request->auth_user_request != NULL)
             p = request->auth_user_request->username();
-
         if (!p)
+#endif
             p = "-";
-
         break;
 
     case 'b':
-        // NP: dynamic location of proxy-port not supported on 3.1
-        // display the generic well-known port instead
-        p = "3128";
+        mb.Printf("%d", getMyPort());
         break;
 
     case 'B':
+        if (building_deny_info_url) break;
         p = request ? ftpUrlWith2f(request) : "[no URL]";
-
         break;
 
     case 'c':
+        if (building_deny_info_url) break;
         p = errorPageName(type);
-
         break;
 
     case 'D':
         if (!allowRecursion)
             p = "%D";  // if recursion is not allowed, do not convert
 #if USE_SSL
