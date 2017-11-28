int
ACLFilledChecklist::fd() const
{
    const auto c = conn();
    return (c && c->clientConnection) ? c->clientConnection->fd : fd_;
}