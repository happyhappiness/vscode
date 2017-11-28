void
Ipc::Mem::Segment::open()
{
    assert(theFD < 0);

    theFD = shm_open(theName.termedBuf(), O_RDWR, 0);
    if (theFD < 0) {
        int xerrno = errno;
        debugs(54, 5, "shm_open " << theName << ": " << xstrerr(xerrno));
        fatalf("Ipc::Mem::Segment::open failed to shm_open(%s): %s\n",
               theName.termedBuf(), xstrerr(xerrno));
    }

    theSize = statSize("Ipc::Mem::Segment::open");

    debugs(54, 3, HERE << "opened " << theName << " segment: " << theSize);

    attach();
}