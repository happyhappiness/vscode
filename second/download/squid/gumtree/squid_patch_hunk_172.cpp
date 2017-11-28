                       "Type",
                       "Tout",
                       "Nread",
                       "Nwrite",
                       "Remote Address",
                       "Description");
-#ifdef _SQUID_MSWIN_
+#if _SQUID_MSWIN_
     storeAppendPrintf(dumpEntry, "---- ---------- ------ ---- -------- -------- --------------------- ------------------------------\n");
 #else
     storeAppendPrintf(dumpEntry, "---- ------ ---- -------- -------- --------------------- ------------------------------\n");
 #endif
 
-    for (i = 0; i < Squid_MaxFD; i++) {
+    for (i = 0; i < Squid_MaxFD; ++i) {
         fd_table[i].dumpStats(*dumpEntry, i);
     }
 }
 
 char const *
 fde::remoteAddr() const
