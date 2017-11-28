     if (Config.max_filedescriptors > Squid_MaxFD) {
         debugs(50, DBG_IMPORTANT, "NOTICE: Could not increase the number of filedescriptors");
     }
 
 #if HAVE_SETRLIMIT && defined(RLIMIT_VMEM)
     if (getrlimit(RLIMIT_VMEM, &rl) < 0) {
-        debugs(50, 0, "getrlimit: RLIMIT_VMEM: " << xstrerror());
+        debugs(50, DBG_CRITICAL, "getrlimit: RLIMIT_VMEM: " << xstrerror());
     } else if (rl.rlim_max > rl.rlim_cur) {
         rl.rlim_cur = rl.rlim_max;	/* set it to the max */
 
         if (setrlimit(RLIMIT_VMEM, &rl) < 0) {
             snprintf(tmp_error_buf, ERROR_BUF_SZ, "setrlimit: RLIMIT_VMEM: %s", xstrerror());
             fatal_dump(tmp_error_buf);
