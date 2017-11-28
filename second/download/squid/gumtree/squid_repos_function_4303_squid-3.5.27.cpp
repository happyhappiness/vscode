void Adaptation::Icap::Options::configure(const HttpReply *reply)
{
    error = NULL; // reset initial "unconfigured" value (or an old error?)

    const HttpHeader *h = &reply->header;

    if (reply->sline.status() != Http::scOkay)
        error = "unsupported status code of OPTIONS response";

    // Methods
    if (h->hasByNameListMember("Methods", "REQMOD", ','))
        cfgMethod(ICAP::methodReqmod);

    if (h->hasByNameListMember("Methods", "RESPMOD", ','))
        cfgMethod(ICAP::methodRespmod);

    service = h->getByName("Service");

    serviceId = h->getByName("ServiceId");

    istag = h->getByName("ISTag");

    if (h->getByName("Opt-body-type").size()) {
        // TODO: add a class to rate-limit such warnings using FadingCounter
        debugs(93,DBG_IMPORTANT, "WARNING: Ignoring unsupported ICAP " <<
               "OPTIONS body; type: " << h->getByName("Opt-body-type"));
        // Do not set error, assuming the response headers are valid.
    }

    cfgIntHeader(h, "Max-Connections", max_connections);
    if (max_connections == 0)
        debugs(93, DBG_IMPORTANT, "WARNING: Max-Connections is set to zero! ");

    cfgIntHeader(h, "Options-TTL", theTTL);

    theTimestamp = h->getTime(HDR_DATE);

    if (theTimestamp < 0)
        theTimestamp = squid_curtime;

    if (h->hasListMember(HDR_ALLOW, "204", ','))
        allow204 = true;

    if (h->hasListMember(HDR_ALLOW, "206", ','))
        allow206 = true;

    cfgIntHeader(h, "Preview", preview);

    cfgTransferList(h, theTransfers.preview);
    cfgTransferList(h, theTransfers.ignore);
    cfgTransferList(h, theTransfers.complete);
}