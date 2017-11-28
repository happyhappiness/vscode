void
StoreEntry::DeferReader(void *theContext, CommRead const &aRead)
{
    StoreEntry *anEntry = (StoreEntry *)theContext;
    anEntry->delayAwareRead(aRead.conn,
                            aRead.buf,
                            aRead.len,
                            aRead.callback);
}