void
ClientSocketContext::doClose()
{
    comm_close(fd());
}