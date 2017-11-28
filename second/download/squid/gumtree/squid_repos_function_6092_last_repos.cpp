int
fcntlLock(const int fd, const short lockType)
{
    // the exact composition and order of flock data members is unknown!
    struct flock fl;
    memset(&fl, 0, sizeof(fl));
    fl.l_type = lockType;
    fl.l_whence = SEEK_SET; // with zero l_len and l_start, means "whole file"
    return ::fcntl(fd, F_SETLK, &fl);
}