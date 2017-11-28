         file_close(swaplog_fd);
 
     /* open a write-only FD for the new log */
     fd = file_open(new_path, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY);
 
     if (fd < 0) {
-        debugs(50, DBG_IMPORTANT, "ERROR: while opening swap log" << new_path << ": " << xstrerror());
+        int xerrno = errno;
+        debugs(50, DBG_IMPORTANT, "ERROR: while opening swap log" << new_path << ": " << xstrerr(xerrno));
         fatalf("Failed to open swap log %s", new_path);
     }
 
     swaplog_fd = fd;
     rebuilding_ = true;
 
