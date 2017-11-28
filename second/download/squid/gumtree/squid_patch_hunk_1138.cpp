     l_stdio_t *ll = static_cast<l_stdio_t*>(xcalloc(1, sizeof(*ll)));
     lf->data = ll;
 
     ll->fd = file_open(path, O_WRONLY | O_CREAT | O_TEXT);
 
     if (DISK_ERROR == ll->fd) {
-        if (ENOENT == errno && fatal_flag) {
+        int xerrno = errno;
+        if (ENOENT == xerrno && fatal_flag) {
             fatalf("Cannot open '%s' because\n"
                    "\tthe parent directory does not exist.\n"
                    "\tPlease create the directory.\n", path);
-        } else if (EACCES == errno && fatal_flag) {
+        } else if (EACCES == xerrno && fatal_flag) {
             fatalf("Cannot open '%s' for writing.\n"
                    "\tThe parent directory must be writeable by the\n"
                    "\tuser '%s', which is the cache_effective_user\n"
                    "\tset in squid.conf.", path, Config.effectiveUser);
-        } else if (EISDIR == errno && fatal_flag) {
+        } else if (EISDIR == xerrno && fatal_flag) {
             fatalf("Cannot open '%s' because it is a directory, not a file.\n", path);
         } else {
-            debugs(50, DBG_IMPORTANT, "ERROR: logfileOpen " << lf->path << ": " << xstrerror());
+            debugs(50, DBG_IMPORTANT, MYNAME << "ERROR: " << lf->path << ": " << xstrerr(xerrno));
             return 0;
         }
     }
     if (bufsz > 0) {
         ll->buf = static_cast<char*>(xmalloc(bufsz));
         ll->bufsz = bufsz;
