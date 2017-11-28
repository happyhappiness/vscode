void
Ftp::Gateway::handleRequestBodyProducerAborted()
{
    Client::handleRequestBodyProducerAborted();
    debugs(9, 3, HERE << "ftpState=" << this);
    failed(ERR_READ_ERROR, 0);
}