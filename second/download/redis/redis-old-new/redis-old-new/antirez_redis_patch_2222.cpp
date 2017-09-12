@@ -2795,6 +2795,8 @@ static int rdbSaveLzfStringObject(FILE *fp, robj *obj) {
     outlen = sdslen(obj->ptr)-4;
     if (outlen <= 0) return 0;
     if ((out = zmalloc(outlen+1)) == NULL) return 0;
+    printf("Calling LZF with ptr: %p\n", (void*)obj->ptr);
+    fflush(stdout);
     comprlen = lzf_compress(obj->ptr, sdslen(obj->ptr), out, outlen);
     if (comprlen == 0) {
         zfree(out);
@@ -5615,6 +5617,7 @@ static sds genRedisInfoString(void) {
             "vm_stats_io_processing_len:%lu\r\n"
             "vm_stats_io_processed_len:%lu\r\n"
             "vm_stats_io_waiting_clients:%lu\r\n"
+            "vm_stats_io_active_threads:%lu\r\n"
             ,(unsigned long long) server.vm_max_memory,
             (unsigned long long) server.vm_page_size,
             (unsigned long long) server.vm_pages,
@@ -5625,7 +5628,8 @@ static sds genRedisInfoString(void) {
             (unsigned long) listLength(server.io_newjobs),
             (unsigned long) listLength(server.io_processing),
             (unsigned long) listLength(server.io_processed),
-            (unsigned long) listLength(server.io_clients)
+            (unsigned long) listLength(server.io_clients),
+            (unsigned long) server.io_active_threads
         );
     }
     for (j = 0; j < server.dbnum; j++) {