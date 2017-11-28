void
Ipc::Mem::Segment::create(const off_t aSize)
{
    assert(aSize > 0);
    assert(theFD < 0);

    theFD = shm_open(theName.termedBuf(), O_CREAT | O_RDWR | O_TRUNC,
                     S_IRUSR | S_IWUSR);
    if (theFD < 0) {
        debugs(54, 5, HERE << "shm_open " << theName << ": " << xstrerror());
        fatalf("Ipc::Mem::Segment::create failed to shm_open(%s): %s\n",
               theName.termedBuf(), xstrerror());
    }

    if (ftruncate(theFD, aSize)) {
        debugs(54, 5, HERE << "ftruncate " << theName << ": " << xstrerror());
        fatalf("Ipc::Mem::Segment::create failed to ftruncate(%s): %s\n",
               theName.termedBuf(), xstrerror());
    }

    assert(statSize("Ipc::Mem::Segment::create") == aSize); // paranoid

    theSize = aSize;
    theReserved = 0;
    doUnlink = true;

    debugs(54, 3, HERE << "created " << theName << " segment: " << theSize);

    attach();
}