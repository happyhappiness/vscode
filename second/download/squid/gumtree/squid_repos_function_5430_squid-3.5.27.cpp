void
Ftp::Channel::forget()
{
    if (Comm::IsConnOpen(conn)) {
        commUnsetConnTimeout(conn);
        comm_remove_close_handler(conn->fd, closer);
    }
    clear();
}