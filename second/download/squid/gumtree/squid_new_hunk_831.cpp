void
Ipc::Mem::Segment::create(const off_t aSize)
{
    assert(aSize > 0);
    assert(theFD < 0);

    // Why a brand new segment? A Squid crash may leave a reusable segment, but
    // our placement-new code requires an all-0s segment. We could truncate and
    // resize the old segment, but OS X does not allow using O_TRUNC with
    // shm_open() and does not support ftruncate() for old segments.
    if (!createFresh() && errno == EEXIST) {
        unlink();
        createFresh();
    }

    if (theFD < 0) {
        debugs(54, 5, HERE << "shm_open " << theName << ": " << xstrerror());
        fatalf("Ipc::Mem::Segment::create failed to shm_open(%s): %s\n",
               theName.termedBuf(), xstrerror());
    }

    if (ftruncate(theFD, aSize)) {
        const int savedError = errno;
        unlink();
        debugs(54, 5, HERE << "ftruncate " << theName << ": " << xstrerr(savedError));
        fatalf("Ipc::Mem::Segment::create failed to ftruncate(%s): %s\n",
               theName.termedBuf(), xstrerr(savedError));
    }
    // We assume that the shm_open(O_CREAT)+ftruncate() combo zeros the segment.

    theSize = statSize("Ipc::Mem::Segment::create");

    // OS X will round up to a full page, so not checking for exact size match.
    assert(theSize >= aSize);

    theReserved = 0;
    doUnlink = true;

    debugs(54, 3, HERE << "created " << theName << " segment: " << theSize);

    attach();
