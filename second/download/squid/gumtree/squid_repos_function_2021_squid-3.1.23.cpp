void
HttpStateData::handleRequestBodyProducerAborted()
{
    ServerStateData::handleRequestBodyProducerAborted();
    // XXX: SendComplete(COMM_ERR_CLOSING) does little. Is it enough?
    CommIoCbParams io(NULL);
    io.fd=fd;
    io.flag=COMM_ERR_CLOSING;
    sendComplete(io);
}