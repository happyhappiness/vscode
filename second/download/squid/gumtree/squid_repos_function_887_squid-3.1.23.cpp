void
comm_close_start(int fd, void *data)
{
#if USE_SSL
    fde *F = &fd_table[fd];
    if (F->ssl)
        ssl_shutdown_method(fd);

#endif

}