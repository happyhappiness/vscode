int
ACLFilledChecklist::fd() const
{
    return (conn_ != NULL && conn_->clientConnection != NULL) ? conn_->clientConnection->fd : fd_;
}