void
Comm::TcpAcceptor::swanSong()
{
    debugs(5,5, HERE);
    unsubscribe("swanSong");
    conn = NULL;
    AcceptLimiter::Instance().removeDead(this);
    AsyncJob::swanSong();
}