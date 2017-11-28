static void
commLingerTimeout(int fd, void *unused)
{
    debugs(5, 3, "commLingerTimeout: FD " << fd);
    comm_close(fd);
}