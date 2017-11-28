void
Mgr::StoreToCommWriter::noteStoreCopied(StoreIOBuffer ioBuf)
{
    debugs(16, 6, HERE);
    Must(!ioBuf.flags.error);
    if (ioBuf.length > 0)
        scheduleCommWrite(ioBuf); // write received action results to client
    else
        Must(doneAll()); // otherwise, why would Store call us with no data?
}