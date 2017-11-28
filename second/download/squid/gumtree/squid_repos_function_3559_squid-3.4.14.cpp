void
ConnStateData::stopSending(const char *error)
{
    debugs(33, 4, HERE << "sending error (" << clientConnection << "): " << error <<
           "; old receiving error: " <<
           (stoppedReceiving() ? stoppedReceiving_ : "none"));

    if (const char *oldError = stoppedSending()) {
        debugs(33, 3, HERE << "already stopped sending: " << oldError);
        return; // nothing has changed as far as this connection is concerned
    }
    stoppedSending_ = error;

    if (!stoppedReceiving()) {
        if (const int64_t expecting = mayNeedToReadMoreBody()) {
            debugs(33, 5, HERE << "must still read " << expecting <<
                   " request body bytes with " << in.notYetUsed << " unused");
            return; // wait for the request receiver to finish reading
        }
    }

    clientConnection->close();
}