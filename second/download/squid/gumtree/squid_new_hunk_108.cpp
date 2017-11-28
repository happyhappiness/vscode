
/**
 * A write has just completed to the client, or we have just realised there is
 * no more data to send.
 */
void
clientWriteComplete(const Comm::ConnectionPointer &conn, char *bufnotused, size_t size, comm_err_t errflag, int xerrno, void *data)
{
    ClientSocketContext *context = (ClientSocketContext *)data;
    context->writeComplete(conn, bufnotused, size, errflag);
}

/// remembers the abnormal connection termination for logging purposes
void
ClientSocketContext::noteIoError(const int xerrno)
{
    if (http) {
        if (xerrno == ETIMEDOUT)
            http->al->http.timedout = true;
        else // even if xerrno is zero (which means read abort/eof)
            http->al->http.aborted = true;
    }
}


void
ClientSocketContext::doClose()
{
    clientConnection->close();
}

/// called when we encounter a response-related error
void
ClientSocketContext::initiateClose(const char *reason)
{
    http->getConn()->stopSending(reason); // closes ASAP
}

void
ConnStateData::stopSending(const char *error)
{
    debugs(33, 4, HERE << "sending error (" << clientConnection << "): " << error <<
           "; old receiving error: " <<
           (stoppedReceiving() ? stoppedReceiving_ : "none"));

    if (const char *oldError = stoppedSending()) {
        debugs(33, 3, HERE << "already stopped sending: " << oldError);
        return; // nothing has changed as far as this connection is concerned
