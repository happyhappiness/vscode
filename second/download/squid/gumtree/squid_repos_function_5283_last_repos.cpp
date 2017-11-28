void
Ftp::Relay::scheduleReadControlReply()
{
    Ftp::Client::scheduleReadControlReply(0);
}