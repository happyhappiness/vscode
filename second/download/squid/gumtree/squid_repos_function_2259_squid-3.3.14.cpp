void
MemObject::kickReads()
{
    deferredReads.kickReads(-1);
}