void
Adaptation::Ecap::XactionRep::updateHistory(HttpMsg *adapted)
{
    if (!theMaster) // all updates rely on being able to query the adapter
        return;

    const HttpRequest *request = dynamic_cast<const HttpRequest*>(theCauseRep ?
                                 theCauseRep->raw().header : theVirginRep.raw().header);
    Must(request);

    // TODO: move common ICAP/eCAP logic to Adaptation::Xaction or similar
    // TODO: optimize Area-to-String conversion

    // update the cross-transactional database if needed
    if (const char *xxNameStr = Adaptation::Config::masterx_shared_name) {
        Adaptation::History::Pointer ah = request->adaptHistory(true);
        if (ah != NULL) {
            libecap::Name xxName(xxNameStr); // TODO: optimize?
            if (const libecap::Area val = theMaster->option(xxName))
                ah->updateXxRecord(xxNameStr, val.toString().c_str());
        }
    }

    // update the adaptation plan if needed
    if (service().cfg().routing) {
        String services;
        if (const libecap::Area services = theMaster->option(libecap::metaNextServices)) {
            Adaptation::History::Pointer ah = request->adaptHistory(true);
            if (ah != NULL)
                ah->updateNextServices(services.toString().c_str());
        }
    } // TODO: else warn (occasionally!) if we got libecap::metaNextServices

    // Store received meta headers for adapt::<last_h logformat code use.
    // If we already have stored headers from a previous adaptation transaction
    // related to the same master transction, they will be replaced.
    Adaptation::History::Pointer ah = request->adaptLogHistory();
    if (ah != NULL) {
        HttpHeader meta(hoReply);
        OptionsExtractor extractor(meta);
        theMaster->visitEachOption(extractor);
        ah->recordMeta(&meta);
    }

    // Add just-created history to the adapted/cloned request that lacks it.
    if (HttpRequest *adaptedReq = dynamic_cast<HttpRequest*>(adapted))
        adaptedReq->adaptHistoryImport(*request);
}