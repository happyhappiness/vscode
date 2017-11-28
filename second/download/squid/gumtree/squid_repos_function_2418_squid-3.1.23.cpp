void
FwdState::startFail()
{
    debugs(17, 3, "fwdStartFail: " << entry->url()  );
    ErrorState *anErr = errorCon(ERR_CANNOT_FORWARD, HTTP_SERVICE_UNAVAILABLE, request);
    anErr->xerrno = errno;
    fail(anErr);
    self = NULL;	// refcounted
}