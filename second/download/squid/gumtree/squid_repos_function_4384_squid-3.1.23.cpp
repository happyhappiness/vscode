int
ACLFilledChecklist::fd() const
{
    return conn_ != NULL ? conn_->fd : fd_;
}