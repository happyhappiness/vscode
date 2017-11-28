void
Ipc::Mem::Segment::attach()
{
    assert(theFD >= 0);
    assert(!theMem);

    // mmap() accepts size_t for the size; we give it off_t which might
    // be bigger; assert overflows until we support multiple mmap()s?
    assert(theSize == static_cast<off_t>(static_cast<size_t>(theSize)));

    void *const p =
        mmap(NULL, theSize, PROT_READ | PROT_WRITE, MAP_SHARED, theFD, 0);
    if (p == MAP_FAILED) {
        int xerrno = errno;
        debugs(54, 5, "mmap " << theName << ": " << xstrerr(xerrno));
        fatalf("Ipc::Mem::Segment::attach failed to mmap(%s): %s\n",
               theName.termedBuf(), xstrerr(xerrno));
    }
    theMem = p;

    lock();
}