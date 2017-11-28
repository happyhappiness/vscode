void
Comm::Connection::close()
{
    if (isOpen()) {
        comm_close(fd);
        noteClosure();
    }
}