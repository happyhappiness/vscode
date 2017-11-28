 }
 
 void
 SwapDir::unlink(StoreEntry &) {}
 
 void
+SwapDir::getStats(StoreInfoStats &stats) const
+{
+    if (!doReportStat())
+        return;
+
+    stats.swap.size = currentSize();
+    stats.swap.capacity = maxSize();
+    stats.swap.count = currentCount();
+}
+
+void
 SwapDir::stat(StoreEntry &output) const
 {
+    if (!doReportStat())
+        return;
+
     storeAppendPrintf(&output, "Store Directory #%d (%s): %s\n", index, type(),
                       path);
     storeAppendPrintf(&output, "FS Block Size %d Bytes\n",
                       fs.blksize);
     statfs(output);
 
