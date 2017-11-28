void
Http::Stream::initiateClose(const char *reason)
{
    debugs(33, 4, clientConnection << " because " << reason);
    getConn()->stopSending(reason); // closes ASAP
}