void
FtpChannel::close()
{
    // channels with active listeners will be closed when the listener handler dies.
    if (Comm::IsConnOpen(conn)) {
        comm_remove_close_handler(conn->fd, closer);
        conn->close(); // we do not expect to be called back
    }
    clear();
}