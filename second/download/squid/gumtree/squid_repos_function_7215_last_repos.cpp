void
Ipc::Mem::Segment::create(const off_t aSize)
{
    assert(aSize > 0);
    assert(theFD < 0);

    int xerrno = 0;

    // Why a brand new segment? A Squid crash may leave a reusable segment, but
    // our placement-new code requires an all-0s segment. We could truncate and
    // resize the old segment, but OS X does not allow using O_TRUNC with
    // shm_open() and does not support ftruncate() for old segments.
    if (!createFresh(xerrno) && xerrno == EEXIST) {
        unlink();
        createFresh(xerrno);
    }

    if (theFD < 0) {
        debugs(54, 5, "shm_open " << theName << ": " << xstrerr(xerrno));
        fatalf("Ipc::Mem::Segment::create failed to shm_open(%s): %s\n",
               theName.termedBuf(), xstrerr(xerrno));
    }

    if (ftruncate(theFD, aSize)) {
        xerrno = errno;
        unlink();
        debugs(54, 5, "ftruncate " << theName << ": " << xstrerr(xerrno));
        fatalf("Ipc::Mem::Segment::create failed to ftruncate(%s): %s\n",
               theName.termedBuf(), xstrerr(xerrno));
    }
    // We assume that the shm_open(O_CREAT)+ftruncate() combo zeros the segment.

    theSize = statSize("Ipc::Mem::Segment::create");

    // OS X will round up to a full page, so not checking for exact size match.
    assert(theSize >= aSize);

    theReserved = 0;
    doUnlink = true;

    debugs(54, 3, "created " << theName << " segment: " << theSize);
    attach();
}