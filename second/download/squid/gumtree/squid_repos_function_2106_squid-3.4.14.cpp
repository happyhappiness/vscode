void
HttpStateData::abortTransaction(const char *reason)
{
    debugs(11,5, HERE << "aborting transaction for " << reason <<
           "; " << serverConnection << ", this " << this);

    if (Comm::IsConnOpen(serverConnection)) {
        serverConnection->close();
        return;
    }

    fwd->handleUnregisteredServerEnd();
    mustStop("HttpStateData::abortTransaction");
}