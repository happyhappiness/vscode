void
FtpStateData::completedListing()
{
    assert(entry);
    entry->lock();
    ErrorState ferr(ERR_DIR_LISTING, Http::scOkay, request);
    ferr.ftp.listing = &listing;
    ferr.ftp.cwd_msg = xstrdup(cwd_message.size()? cwd_message.termedBuf() : "");
    ferr.ftp.server_msg = ctrl.message;
    ctrl.message = NULL;
    entry->replaceHttpReply( ferr.BuildHttpReply() );
    EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);
    entry->flush();
    entry->unlock();
}