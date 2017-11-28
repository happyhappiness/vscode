void
DeferredReadManager::kickARead(DeferredRead const &aRead)
{
    if (aRead.cancelled)
        return;

    if (aRead.theRead.fd>=0 && fd_table[aRead.theRead.fd].closing())
        return;

    debugs(5, 3, "Kicking deferred read on FD " << aRead.theRead.fd);

    aRead.theReader(aRead.theContext, aRead.theRead);
}