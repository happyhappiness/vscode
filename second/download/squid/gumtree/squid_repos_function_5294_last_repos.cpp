void
Ftp::Client::start()
{
    scheduleReadControlReply(0);
}