int
ACLFilledChecklist::fd() const
{
    const ConnStateData *c = conn();
    return (c != NULL && c->clientConnection != NULL) ? c->clientConnection->fd : fd_;
}