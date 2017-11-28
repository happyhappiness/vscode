void
Ftp::Relay::failedErrorMessage(err_type error, int xerrno)
{
    const Http::StatusCode httpStatus = failedHttpStatus(error);
    HttpReply *const reply = createHttpReply(httpStatus);
    entry->replaceHttpReply(reply);
    EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);
    fwd->request->detailError(error, xerrno);
}