void
Ftp::Relay::start()
{
    if (!master().clientReadGreeting)
        Ftp::Client::start();
    else if (serverState() == fssHandleDataRequest ||
             serverState() == fssHandleUploadRequest)
        handleDataRequest();
    else
        sendCommand();
}