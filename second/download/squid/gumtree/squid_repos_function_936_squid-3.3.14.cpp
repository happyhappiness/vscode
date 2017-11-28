void
DeferredReadManager::kickARead(DeferredRead const &aRead)
{
    if (aRead.cancelled)
        return;

    if (Comm::IsConnOpen(aRead.theRead.conn) && fd_table[aRead.theRead.conn->fd].closing())
        return;

    debugs(5, 3, "Kicking deferred read on " << aRead.theRead.conn);

    aRead.theReader(aRead.theContext, aRead.theRead);
}