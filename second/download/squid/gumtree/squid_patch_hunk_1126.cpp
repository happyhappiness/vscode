     // be bigger; assert overflows until we support multiple mmap()s?
     assert(theSize == static_cast<off_t>(static_cast<size_t>(theSize)));
 
     void *const p =
         mmap(NULL, theSize, PROT_READ | PROT_WRITE, MAP_SHARED, theFD, 0);
     if (p == MAP_FAILED) {
-        debugs(54, 5, HERE << "mmap " << theName << ": " << xstrerror());
+        int xerrno = errno;
+        debugs(54, 5, "mmap " << theName << ": " << xstrerr(xerrno));
         fatalf("Ipc::Mem::Segment::attach failed to mmap(%s): %s\n",
-               theName.termedBuf(), xstrerror());
+               theName.termedBuf(), xstrerr(xerrno));
     }
     theMem = p;
+
+    lock();
 }
 
 /// Unmap the shared memory segment from the process memory space.
 void
 Ipc::Mem::Segment::detach()
 {
     if (!theMem)
         return;
 
     if (munmap(theMem, theSize)) {
-        debugs(54, 5, HERE << "munmap " << theName << ": " << xstrerror());
+        int xerrno = errno;
+        debugs(54, 5, "munmap " << theName << ": " << xstrerr(xerrno));
         fatalf("Ipc::Mem::Segment::detach failed to munmap(%s): %s\n",
-               theName.termedBuf(), xstrerror());
+               theName.termedBuf(), xstrerr(xerrno));
     }
     theMem = 0;
 }
 
+/// Lock the segment into RAM, ensuring that the OS has enough RAM for it [now]
+/// and preventing segment bytes from being swapped out to disk later by the OS.
+void
+Ipc::Mem::Segment::lock()
+{
+    if (!Config.shmLocking) {
+        debugs(54, 5, "mlock(2)-ing disabled");
+        return;
+    }
+
+#if defined(_POSIX_MEMLOCK_RANGE)
+    debugs(54, 7, "mlock(" << theName << ',' << theSize << ") starts");
+    if (mlock(theMem, theSize) != 0) {
+        const int savedError = errno;
+        fatalf("shared_memory_locking on but failed to mlock(%s, %" PRId64 "): %s\n",
+               theName.termedBuf(),static_cast<int64_t>(theSize), xstrerr(savedError));
+    }
+    // TODO: Warn if it took too long.
+    debugs(54, 7, "mlock(" << theName << ',' << theSize << ") OK");
+#else
+    debugs(54, 5, "insufficient mlock(2) support");
+    if (Config.shmLocking.configured()) { // set explicitly
+        static bool warnedOnce = false;
+        if (!warnedOnce) {
+            debugs(54, DBG_IMPORTANT, "ERROR: insufficient mlock(2) support prevents " <<
+                   "honoring `shared_memory_locking on`. " <<
+                   "If you lack RAM, kernel will kill Squid later.");
+            warnedOnce = true;
+        }
+    }
+#endif
+}
+
 void
 Ipc::Mem::Segment::unlink()
 {
-    if (shm_unlink(theName.termedBuf()) != 0)
-        debugs(54, 5, HERE << "shm_unlink(" << theName << "): " << xstrerror());
-    else
-        debugs(54, 3, HERE << "unlinked " << theName << " segment");
+    if (shm_unlink(theName.termedBuf()) != 0) {
+        int xerrno = errno;
+        debugs(54, 5, "shm_unlink(" << theName << "): " << xstrerr(xerrno));
+    } else
+        debugs(54, 3, "unlinked " << theName << " segment");
 }
 
 /// determines the size of the underlying "file"
 off_t
 Ipc::Mem::Segment::statSize(const char *context) const
 {
     Must(theFD >= 0);
 
     struct stat s;
     memset(&s, 0, sizeof(s));
 
     if (fstat(theFD, &s) != 0) {
-        debugs(54, 5, HERE << context << " fstat " << theName << ": " << xstrerror());
+        int xerrno = errno;
+        debugs(54, 5, context << " fstat " << theName << ": " << xstrerr(xerrno));
         fatalf("Ipc::Mem::Segment::statSize: %s failed to fstat(%s): %s\n",
-               context, theName.termedBuf(), xstrerror());
+               context, theName.termedBuf(), xstrerr(xerrno));
     }
 
     return s.st_size;
 }
 
 /// Generate name for shared memory segment. Starts with a prefix required
