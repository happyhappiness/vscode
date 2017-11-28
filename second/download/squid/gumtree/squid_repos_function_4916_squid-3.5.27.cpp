void
ACLFilledChecklist::fd(int aDescriptor)
{
    const ConnStateData *c = conn();
    assert(!c || !c->clientConnection || c->clientConnection->fd == aDescriptor);
    fd_ = aDescriptor;
}