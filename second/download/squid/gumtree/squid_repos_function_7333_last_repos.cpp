void
Mgr::Forwarder::handleError()
{
    debugs(16, DBG_CRITICAL, "ERROR: uri " << entry->url() << " exceeds buffer size");
    sendError(new ErrorState(ERR_INVALID_URL, Http::scUriTooLong, httpRequest));
    mustStop("long URI");
}