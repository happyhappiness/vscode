void
ACLFilledChecklist::fd(int aDescriptor)
{
    const auto c = conn();
    assert(!c || !c->clientConnection || c->clientConnection->fd == aDescriptor);
    fd_ = aDescriptor;
}