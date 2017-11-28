     storeAppendPrintf(&sentry, "\n");
 }
 
 void
 CossSwapDir::parse(int anIndex, char *aPath)
 {
-    unsigned int i;
-    unsigned int size;
-    off_t max_offset;
-
-    i = GetInteger();
-    size = i << 10;		/* Mbytes to Kbytes */
-
-    if (size <= 0)
+    const int i = GetInteger();
+    if (i <= 0)
         fatal("storeCossDirParse: invalid size value");
 
     index = anIndex;
 
     path = xstrdup(aPath);
 
-    max_size = size;
+    max_size = static_cast<uint64_t>(i) << 20; // MBytes to Bytes
 
     parseOptions(0);
 
     if (NULL == io)
         changeIO(DiskIOModule::FindDefault());
 
