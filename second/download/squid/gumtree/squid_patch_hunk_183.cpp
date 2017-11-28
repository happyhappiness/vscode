 void
 UFSSwapDir::sync()
 {
     IO->sync();
 }
 
+void
+UFSSwapDir::swappedOut(const StoreEntry &e)
+{
+    cur_size += fs.blksize * sizeInBlocks(e.swap_file_sz);
+    ++n_disk_objects;
+}
+
 StoreSearch *
 UFSSwapDir::search(String const url, HttpRequest *request)
 {
     if (url.size())
         fatal ("Cannot search by url yet\n");
 
