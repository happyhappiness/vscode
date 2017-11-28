void
MemObject::delayRead(DeferredRead const &aRead)
{
    deferredReads.delayRead(aRead);
}