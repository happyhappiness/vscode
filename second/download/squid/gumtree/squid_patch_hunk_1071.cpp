 }
 
 // report Rock DB creation error and exit
 void
 Rock::SwapDir::createError(const char *const msg)
 {
+    int xerrno = errno; // XXX: where does errno come from?
     debugs(47, DBG_CRITICAL, "ERROR: Failed to initialize Rock Store db in " <<
-           filePath << "; " << msg << " error: " << xstrerror());
+           filePath << "; " << msg << " error: " << xstrerr(xerrno));
     fatal("Rock Store db creation error");
 }
 
 void
 Rock::SwapDir::init()
 {
