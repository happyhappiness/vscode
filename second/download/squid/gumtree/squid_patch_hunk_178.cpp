         fatal("COSS requires max-size to be set to something other than -1!\n");
 
     if (max_objsize > COSS_MEMBUF_SZ)
         fatalf("COSS max-size option must be less than COSS_MEMBUF_SZ (%d)\n",
                COSS_MEMBUF_SZ);
 
-    /*
-     * check that we won't overflow sfileno later.  0xFFFFFF is the
-     * largest possible sfileno, assuming sfileno is a 25-bit
-     * signed integer, as defined in structs.h.
-     */
-    max_offset = (off_t) 0xFFFFFF << blksz_bits;
+    // check that we won't overflow sfileno later.
+    const uint64_t max_offset = (uint64_t)SwapFilenMax << blksz_bits;
 
-    if ((off_t)max_size > (max_offset>>10)) {
+    if (maxSize() > max_offset) {
         debugs(47, 0, "COSS block-size = " << (1<<blksz_bits) << " bytes");
         debugs(47,0, "COSS largest file offset = " << (max_offset >> 10) << " KB");
-        debugs(47, 0, "COSS cache_dir size = " << max_size << " KB");
+        debugs(47, 0, "COSS cache_dir size = " << (maxSize() >> 10) << " KB");
         fatal("COSS cache_dir size exceeds largest offset\n");
     }
 }
 
 
 void
-CossSwapDir::reconfigure(int index, char *path)
+CossSwapDir::reconfigure()
 {
-    unsigned int i;
-    unsigned int size;
-
-    i = GetInteger();
-    size = i << 10;		/* Mbytes to Kbytes */
-
-    if (size <= 0)
+    const int i = GetInteger();
+    if (i <= 0)
         fatal("storeCossDirParse: invalid size value");
 
-    if (size == (size_t)max_size)
-        debugs(3, 1, "Cache COSS dir '" << path << "' size remains unchanged at " << size << " KB");
+    const uint64_t size = static_cast<uint64_t>(i) << 20; // MBytes to Bytes
+
+    if (size == maxSize())
+        debugs(3, 1, "Cache COSS dir '" << path << "' size remains unchanged at " << i << " MB");
     else {
-        debugs(3, 1, "Cache COSS dir '" << path << "' size changed to " << size << " KB");
+        debugs(3, 1, "Cache COSS dir '" << path << "' size changed to " << i << " MB");
         max_size = size;
     }
 
     /* Enforce maxobjsize being set to something */
     if (max_objsize == -1)
         fatal("COSS requires max-size to be set to something other than -1!\n");
 }
 
 void
+CossSwapDir::swappedOut(const StoreEntry &e)
+{
+    cur_size += fs.blksize * sizeInBlocks(e.swap_file_sz);
+    ++n_disk_objects;
+}
+
+void
 CossSwapDir::dump(StoreEntry &entry)const
 {
-    storeAppendPrintf(&entry, " %" PRIu64, (max_size >> 10));
+    storeAppendPrintf(&entry, " %" PRIu64, maxSize() >> 20);
     dumpOptions(&entry);
 }
 
-CossSwapDir::CossSwapDir() : SwapDir ("coss"), swaplog_fd(-1), count(0), current_membuf (NULL), current_offset(0), numcollisions(0),  blksz_bits(0), io (NULL), ioModule(NULL), currentIOOptions(new ConfigOptionVector()), stripe_path(NULL)
+CossSwapDir::CossSwapDir() : SwapDir ("coss"), swaplog_fd(-1), count(0), current_membuf (NULL), current_offset(0), numcollisions(0),  blksz_bits(0), io (NULL), ioModule(NULL), currentIOOptions(new ConfigOptionVector()), stripe_path(NULL), cur_size(0), n_disk_objects(0)
 {
     membufs.head = NULL;
     membufs.tail = NULL;
     cossindex.head = NULL;
     cossindex.tail = NULL;
     blksz_mask = (1 << blksz_bits) - 1;
