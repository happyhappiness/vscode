void
Ftp::Relay::proceedAfterPreliminaryReply()
{
    debugs(9, 5, "proceeding after preliminary reply to client");

    Must(thePreliminaryCb != NULL);
    const PreliminaryCb cb = thePreliminaryCb;
    thePreliminaryCb = NULL;
    (this->*cb)();
}