void
Ftp::Relay::forwardReply()
{
    assert(entry->isEmpty());
    EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);

    HttpReply *const reply = createHttpReply(Http::scNoContent);
    reply->sources |= HttpMsg::srcFtp;

    setVirginReply(reply);
    adaptOrFinalizeReply();

    serverComplete();
}