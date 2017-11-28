void
StoreEntry::DeferReader(void *theContext, CommRead const &aRead)
{
    StoreEntry *anEntry = (StoreEntry *)theContext;
    anEntry->delayAwareRead(aRead.fd,
                            aRead.buf,
                            aRead.len,
                            aRead.callback);
}