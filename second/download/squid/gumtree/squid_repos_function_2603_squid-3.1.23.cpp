void
FtpChannel::close()
{
    if (fd >= 0) {
        comm_remove_close_handler(fd, closer);
        closer = NULL;
        comm_close(fd); // we do not expect to be called back
        fd = -1;
    }
}