void
ACLFilledChecklist::fd(int aDescriptor)
{
    assert(!conn() || conn()->clientConnection == NULL || conn()->clientConnection->fd == aDescriptor);
    fd_ = aDescriptor;
}