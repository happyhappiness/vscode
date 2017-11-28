
// premature end of the request body
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

// called when we wrote request headers(!) or a part of the body
void
HttpStateData::sentRequestBody(const CommIoCbParams &io)
{
