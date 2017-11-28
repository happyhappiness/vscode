void
Comm::ConnOpener::keepFd()
{
    Must(conn_ != NULL);
    Must(temporaryFd_ >= 0);

    cleanFd();

    conn_->fd = temporaryFd_;
    temporaryFd_ = -1;
}