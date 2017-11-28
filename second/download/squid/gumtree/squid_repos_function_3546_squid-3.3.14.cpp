void
ConnStateData::clientAfterReadingRequests()
{
    // Were we expecting to read more request body from half-closed connection?
    if (mayNeedToReadMoreBody() && commIsHalfClosed(clientConnection->fd)) {
        debugs(33, 3, HERE << "truncated body: closing half-closed " << clientConnection);
        clientConnection->close();
        return;
    }

    if (flags.readMore)
        readSomeData();
}