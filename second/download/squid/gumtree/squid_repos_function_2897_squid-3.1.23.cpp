bool HttpRequest::inheritProperties(const HttpMsg *aMsg)
{
    const HttpRequest* aReq = dynamic_cast<const HttpRequest*>(aMsg);
    if (!aReq)
        return false;

    client_addr = aReq->client_addr;
#if FOLLOW_X_FORWARDED_FOR
    indirect_client_addr = aReq->indirect_client_addr;
#endif
    my_addr = aReq->my_addr;

    dnsWait = aReq->dnsWait;

#if USE_ADAPTATION
    adaptHistory_ = aReq->adaptHistory();
#endif
#if ICAP_CLIENT
    icapHistory_ = aReq->icapHistory();
#endif

    // This may be too conservative for the 204 No Content case
    // may eventually need cloneNullAdaptationImmune() for that.
    flags = aReq->flags.cloneAdaptationImmune();

    if (aReq->auth_user_request) {
        auth_user_request = aReq->auth_user_request;
        AUTHUSERREQUESTLOCK(auth_user_request, "inheritProperties");
    }

    if (aReq->pinned_connection) {
        pinned_connection = cbdataReference(aReq->pinned_connection);
    }
    return true;
}