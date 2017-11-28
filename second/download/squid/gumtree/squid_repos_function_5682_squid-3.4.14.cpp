void *
Mmapping::map()
{
    // mmap(2) requires that offset is a multiple of the page size
    static const int pageSize = getpagesize();
    delta = offset % pageSize;

    buf = mmap(NULL, length + delta, prot, flags, fd, offset - delta);

    if (buf == MAP_FAILED) {
        const int errNo = errno;
        debugs(79,3, HERE << "error FD " << fd << "mmap(" << length << '+' <<
               delta << ", " << offset << '-' << delta << "): " << xstrerr(errNo));
        buf = NULL;
        return NULL;
    }

    return static_cast<char*>(buf) + delta;
}