void
ClientHttpRequest::calloutsError(const err_type error, const int errDetail)
{
    // The original author of the code also wanted to pass an errno to
    // setReplyToError, but it seems unlikely that the errno reflects the
    // true cause of the error at this point, so I did not pass it.
    if (calloutContext) {
        Ip::Address noAddr;
        noAddr.setNoAddr();
        ConnStateData * c = getConn();
        calloutContext->error = clientBuildError(error, Http::scInternalServerError,
                                NULL,
                                c != NULL ? c->clientConnection->remote : noAddr,
                                request
                                                );
#if USE_AUTH
        calloutContext->error->auth_user_request =
            c != NULL && c->getAuth() != NULL ? c->getAuth() : request->auth_user_request;
#endif
        calloutContext->error->detailError(errDetail);
        calloutContext->readNextRequest = true;
        if (c != NULL)
            c->expectNoForwarding();
    }
    //else if(calloutContext == NULL) is it possible?
}