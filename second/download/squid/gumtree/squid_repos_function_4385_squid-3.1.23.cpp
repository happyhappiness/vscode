void
ACLFilledChecklist::fd(int aDescriptor)
{
    assert(!conn() || conn()->fd == aDescriptor);
    fd_ = aDescriptor;
}