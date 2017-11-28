void
Comm::TcpAcceptor::swanSong()
{
    debugs(5,5, HERE);
    unsubscribe("swanSong");
    if (IsConnOpen(conn)) {
        if (closer_ != NULL)
            comm_remove_close_handler(conn->fd, closer_);
        conn->close();
    }

    conn = NULL;
    AcceptLimiter::Instance().removeDead(this);
    AsyncJob::swanSong();
}