void
ClientSocketContext::initiateClose(const char *reason)
{
    http->getConn()->stopSending(reason); // closes ASAP
}