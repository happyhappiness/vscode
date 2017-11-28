void
ConnStateData::stopReceiving(const char *error)
{
    debugs(33, 4, HERE << "receiving error (" << clientConnection << "): " << error <<
           "; old sending error: " <<
           (stoppedSending() ? stoppedSending_ : "none"));

    if (const char *oldError = stoppedReceiving()) {
        debugs(33, 3, HERE << "already stopped receiving: " << oldError);
        return; // nothing has changed as far as this connection is concerned
    }

    stoppedReceiving_ = error;

    if (const char *sendError = stoppedSending()) {
        debugs(33, 3, HERE << "closing because also stopped sending: " << sendError);
        clientConnection->close();
    }
}