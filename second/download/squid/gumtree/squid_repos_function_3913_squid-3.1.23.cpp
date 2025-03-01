void Adaptation::Icap::ModXact::parseIcapHead()
{
    Must(state.sending == State::sendingUndecided);

    if (!parseHead(icapReply))
        return;

    if (httpHeaderHasConnDir(&icapReply->header, "close")) {
        debugs(93, 5, HERE << "found connection close");
        reuseConnection = false;
    }

    switch (icapReply->sline.status) {

    case 100:
        handle100Continue();
        break;

    case 200:
    case 201: // Symantec Scan Engine 5.0 and later when modifying HTTP msg

        if (!validate200Ok()) {
            throw TexcHere("Invalid ICAP Response");
        } else {
            handle200Ok();
        }

        break;

    case 204:
        handle204NoContent();
        break;

    default:
        debugs(93, 5, HERE << "ICAP status " << icapReply->sline.status);
        handleUnknownScode();
        break;
    }

    const HttpRequest *request = dynamic_cast<HttpRequest*>(adapted.header);
    if (!request)
        request = &virginRequest();

    // update the cross-transactional database if needed (all status codes!)
    if (const char *xxName = Adaptation::Config::masterx_shared_name) {
        Adaptation::History::Pointer ah = request->adaptHistory(true);
        if (ah != NULL) {
            const String val = icapReply->header.getByName(xxName);
            if (val.size() > 0) // XXX: HttpHeader lacks empty value detection
                ah->updateXxRecord(xxName, val);
        }
    }

    // update the adaptation plan if needed (all status codes!)
    if (service().cfg().routing) {
        String services;
        if (icapReply->header.getList(HDR_X_NEXT_SERVICES, &services)) {
            Adaptation::History::Pointer ah = request->adaptHistory(true);
            if (ah != NULL)
                ah->updateNextServices(services);
        }
    } // TODO: else warn (occasionally!) if we got HDR_X_NEXT_SERVICES

    // We need to store received ICAP headers for <icapLastHeader logformat option.
    // If we already have stored headers from previous ICAP transaction related to this
    // request, old headers will be replaced with the new one.

    Adaptation::Icap::History::Pointer h = request->icapHistory();
    if (h != NULL) {
        h->mergeIcapHeaders(&icapReply->header);
        h->setIcapLastHeader(&icapReply->header);
    }

    // handle100Continue() manages state.writing on its own.
    // Non-100 status means the server needs no postPreview data from us.
    if (state.writing == State::writingPaused)
        stopWriting(true);
}