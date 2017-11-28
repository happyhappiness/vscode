void
Ftp::Relay::handleRequestBodyProducerAborted()
{
    ::Client::handleRequestBodyProducerAborted();

    failed(ERR_READ_ERROR);
}