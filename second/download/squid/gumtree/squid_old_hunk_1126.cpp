    // be bigger; assert overflows until we support multiple mmap()s?
    assert(theSize == static_cast<off_t>(static_cast<size_t>(theSize)));

    void *const p =
        mmap(NULL, theSize, PROT_READ | PROT_WRITE, MAP_SHARED, theFD, 0);
    if (p == MAP_FAILED) {
        debugs(54, 5, HERE << "mmap " << theName << ": " << xstrerror());
        fatalf("Ipc::Mem::Segment::attach failed to mmap(%s): %s\n",
               theName.termedBuf(), xstrerror());
    }
    theMem = p;
}

/// Unmap the shared memory segment from the process memory space.
void
Ipc::Mem::Segment::detach()
{
    if (!theMem)
        return;

    if (munmap(theMem, theSize)) {
        debugs(54, 5, HERE << "munmap " << theName << ": " << xstrerror());
        fatalf("Ipc::Mem::Segment::detach failed to munmap(%s): %s\n",
               theName.termedBuf(), xstrerror());
    }
    theMem = 0;
}

void
Ipc::Mem::Segment::unlink()
{
    if (shm_unlink(theName.termedBuf()) != 0)
        debugs(54, 5, HERE << "shm_unlink(" << theName << "): " << xstrerror());
    else
        debugs(54, 3, HERE << "unlinked " << theName << " segment");
}

/// determines the size of the underlying "file"
off_t
Ipc::Mem::Segment::statSize(const char *context) const
{
    Must(theFD >= 0);

    struct stat s;
    memset(&s, 0, sizeof(s));

    if (fstat(theFD, &s) != 0) {
        debugs(54, 5, HERE << context << " fstat " << theName << ": " << xstrerror());
        fatalf("Ipc::Mem::Segment::statSize: %s failed to fstat(%s): %s\n",
               context, theName.termedBuf(), xstrerror());
    }

    return s.st_size;
}

/// Generate name for shared memory segment. Starts with a prefix required
