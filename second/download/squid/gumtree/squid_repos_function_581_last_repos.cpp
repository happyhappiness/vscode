static void
commLingerClose(int fd, void *unused)
{
    LOCAL_ARRAY(char, buf, 1024);
    int n = FD_READ_METHOD(fd, buf, 1024);
    if (n < 0) {
        int xerrno = errno;
        debugs(5, 3, "FD " << fd << " read: " << xstrerr(xerrno));
    }
    comm_close(fd);
}