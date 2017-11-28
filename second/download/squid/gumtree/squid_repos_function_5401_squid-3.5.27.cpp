void
Ftp::Relay::forwardReply()
{
    assert(entry->isEmpty());
    EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);

    HttpReply *const reply = createHttpReply(Http::scNoContent);

    setVirginReply(reply);
    adaptOrFinalizeReply();

    serverComplete();
}