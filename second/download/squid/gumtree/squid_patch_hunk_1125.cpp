 void
 Ipc::Mem::Segment::create(const off_t aSize)
 {
     assert(aSize > 0);
     assert(theFD < 0);
 
+    int xerrno = 0;
+
     // Why a brand new segment? A Squid crash may leave a reusable segment, but
     // our placement-new code requires an all-0s segment. We could truncate and
     // resize the old segment, but OS X does not allow using O_TRUNC with
     // shm_open() and does not support ftruncate() for old segments.
-    if (!createFresh() && errno == EEXIST) {
+    if (!createFresh(xerrno) && xerrno == EEXIST) {
         unlink();
-        createFresh();
+        createFresh(xerrno);
     }
 
     if (theFD < 0) {
-        debugs(54, 5, HERE << "shm_open " << theName << ": " << xstrerror());
+        debugs(54, 5, "shm_open " << theName << ": " << xstrerr(xerrno));
         fatalf("Ipc::Mem::Segment::create failed to shm_open(%s): %s\n",
-               theName.termedBuf(), xstrerror());
+               theName.termedBuf(), xstrerr(xerrno));
     }
 
     if (ftruncate(theFD, aSize)) {
-        const int savedError = errno;
+        xerrno = errno;
         unlink();
-        debugs(54, 5, HERE << "ftruncate " << theName << ": " << xstrerr(savedError));
+        debugs(54, 5, "ftruncate " << theName << ": " << xstrerr(xerrno));
         fatalf("Ipc::Mem::Segment::create failed to ftruncate(%s): %s\n",
-               theName.termedBuf(), xstrerr(savedError));
+               theName.termedBuf(), xstrerr(xerrno));
     }
     // We assume that the shm_open(O_CREAT)+ftruncate() combo zeros the segment.
 
     theSize = statSize("Ipc::Mem::Segment::create");
 
     // OS X will round up to a full page, so not checking for exact size match.
     assert(theSize >= aSize);
 
     theReserved = 0;
     doUnlink = true;
 
-    debugs(54, 3, HERE << "created " << theName << " segment: " << theSize);
-
+    debugs(54, 3, "created " << theName << " segment: " << theSize);
     attach();
 }
 
 void
 Ipc::Mem::Segment::open()
 {
     assert(theFD < 0);
 
     theFD = shm_open(theName.termedBuf(), O_RDWR, 0);
     if (theFD < 0) {
-        debugs(54, 5, HERE << "shm_open " << theName << ": " << xstrerror());
+        int xerrno = errno;
+        debugs(54, 5, "shm_open " << theName << ": " << xstrerr(xerrno));
         fatalf("Ipc::Mem::Segment::open failed to shm_open(%s): %s\n",
-               theName.termedBuf(), xstrerror());
+               theName.termedBuf(), xstrerr(xerrno));
     }
 
     theSize = statSize("Ipc::Mem::Segment::open");
 
     debugs(54, 3, HERE << "opened " << theName << " segment: " << theSize);
 
     attach();
 }
 
 /// Creates a brand new shared memory segment and returns true.
 /// Fails and returns false if there exist an old segment with the same name.
 bool
-Ipc::Mem::Segment::createFresh()
+Ipc::Mem::Segment::createFresh(int &xerrno)
 {
     theFD = shm_open(theName.termedBuf(),
                      O_EXCL | O_CREAT | O_RDWR,
                      S_IRUSR | S_IWUSR);
+    xerrno = errno;
     return theFD >= 0;
 }
 
 /// Map the shared memory segment to the process memory space.
 void
 Ipc::Mem::Segment::attach()
