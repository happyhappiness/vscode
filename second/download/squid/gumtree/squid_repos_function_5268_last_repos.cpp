void
Ftp::Relay::startDataDownload()
{
    assert(Comm::IsConnOpen(data.conn));

    debugs(9, 3, "begin data transfer from " << data.conn->remote <<
           " (" << data.conn->local << ")");

    HttpReply *const reply = createHttpReply(Http::scOkay, -1);
    reply->sources |= HttpMsg::srcFtp;

    EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);
    setVirginReply(reply);
    adaptOrFinalizeReply();

    maybeReadVirginBody();
    state = READING_DATA;
}