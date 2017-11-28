void
HttpStateData::closeServer()
{
    debugs(11,5, HERE << "closing HTTP server FD " << fd << " this " << this);

    if (fd >= 0) {
        fwd->unregister(fd);
        comm_remove_close_handler(fd, closeHandler);
        closeHandler = NULL;
        comm_close(fd);
        fd = -1;
    }
}