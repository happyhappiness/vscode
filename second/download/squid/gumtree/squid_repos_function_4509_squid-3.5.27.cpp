void
Ssl::PeerConnector::start()
{
    AsyncJob::start();

    if (prepareSocket()) {
        initializeSsl();
        negotiateSsl();
    }
}