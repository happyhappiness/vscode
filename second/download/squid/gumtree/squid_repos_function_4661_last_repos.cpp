void
Ftp::Server::startWaitingForOrigin()
{
    if (!isOpen()) // if we are closing, nothing to do
        return;

    debugs(33, 5, "waiting for Ftp::Client data transfer to end");
    waitingForOrigin = true;
}