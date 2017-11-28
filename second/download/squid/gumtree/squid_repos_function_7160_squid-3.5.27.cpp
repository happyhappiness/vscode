void
Mgr::Forwarder::sendError(ErrorState *error)
{
    debugs(16, 3, HERE);
    Must(error != NULL);
    Must(entry != NULL);
    Must(httpRequest != NULL);

    EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);
    entry->buffer();
    entry->replaceHttpReply(error->BuildHttpReply());
    entry->expires = squid_curtime;
    delete error;
    entry->flush();
    entry->complete();
}