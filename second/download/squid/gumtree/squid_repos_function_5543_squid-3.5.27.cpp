bool
Ftp::Gateway::mayReadVirginReplyBody() const
{
    // TODO: Can we do what Ftp::Relay::mayReadVirginReplyBody() does instead?
    return !doneWithServer();
}