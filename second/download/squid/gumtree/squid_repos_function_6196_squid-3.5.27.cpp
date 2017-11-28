bool
Mmapping::unmap()
{
    debugs(79,9, HERE << "FD " << fd <<
           " munmap(" << buf << ", " << length << '+' << delta << ')');

    if (!buf) // forgot or failed to map
        return false;

    const bool error = munmap(buf, length + delta) != 0;
    if (error) {
        const int errNo = errno;
        debugs(79,3, HERE << "error FD " << fd <<
               " munmap(" << buf << ", " << length << '+' << delta << "): " <<
               "): " << xstrerr(errNo));
    }
    buf = NULL;
    return !error;
}