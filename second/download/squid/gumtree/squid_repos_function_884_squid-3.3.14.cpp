static void
commLingerClose(int fd, void *unused)
{
    LOCAL_ARRAY(char, buf, 1024);
    int n;
    n = FD_READ_METHOD(fd, buf, 1024);

    if (n < 0)
        debugs(5, 3, "commLingerClose: FD " << fd << " read: " << xstrerror());

    comm_close(fd);
}