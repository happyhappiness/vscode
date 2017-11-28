void
Ftp::Relay::completeForwarding()
{
    debugs(9, 5, forwardingCompleted);
    if (forwardingCompleted)
        return;
    forwardingCompleted = true;
    Ftp::Client::completeForwarding();
}