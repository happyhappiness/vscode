     if (flags.useragent)
         strcat (tempstr, "User-Agent ");
 
     if (!tempstr[0])
         return;
 
-    String strVary (rep->header.getList (HDR_VARY));
+    String strVary (rep->header.getList (Http::HdrType::VARY));
 
     if (!strVary.size() || strVary[0] != '*') {
-        rep->header.putStr (HDR_VARY, tempstr);
+        rep->header.putStr (Http::HdrType::VARY, tempstr);
     }
 }
 
