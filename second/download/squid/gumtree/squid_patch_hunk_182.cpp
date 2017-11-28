     repl->Remove(repl, e, &e->repl);
 }
 
 void
 UFSSwapDir::dump(StoreEntry & entry) const
 {
-    storeAppendPrintf(&entry, " %" PRIu64 " %d %d",
-                      (max_size >> 10),
-                      l1,
-                      l2);
+    storeAppendPrintf(&entry, " %" PRIu64 " %d %d", maxSize() >> 20, l1, l2);
     dumpOptions(&entry);
 }
 
 char *
 UFSSwapDir::fullPath(sfileno filn, char *fullpath) const
 {
-    LOCAL_ARRAY(char, fullfilename, SQUID_MAXPATHLEN);
+    LOCAL_ARRAY(char, fullfilename, MAXPATHLEN);
     int L1 = l1;
     int L2 = l2;
 
     if (!fullpath)
         fullpath = fullfilename;
 
     fullpath[0] = '\0';
 
-    snprintf(fullpath, SQUID_MAXPATHLEN, "%s/%02X/%02X/%08X",
+    snprintf(fullpath, MAXPATHLEN, "%s/%02X/%02X/%08X",
              path,
              ((filn / L2) / L2) % L1,
              (filn / L2) % L2,
              filn);
 
     return fullpath;
