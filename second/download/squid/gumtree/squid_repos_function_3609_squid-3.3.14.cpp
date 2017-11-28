bool
storeRebuildLoadEntry(int fd, int diskIndex, MemBuf &buf,
                      StoreRebuildData &counts)
{
    if (fd < 0)
        return false;

    assert(buf.hasSpace()); // caller must allocate

    const int len = FD_READ_METHOD(fd, buf.space(), buf.spaceSize());
    ++ statCounter.syscalls.disk.reads;
    if (len < 0) {
        const int xerrno = errno;
        debugs(47, DBG_IMPORTANT, "WARNING: cache_dir[" << diskIndex << "]: " <<
               "Ignoring cached entry after meta data read failure: " << xstrerr(xerrno));
        return false;
    }

    buf.appended(len);
    return true;
}