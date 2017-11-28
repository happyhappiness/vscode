void
Adaptation::Ecap::XactionRep::updateSources(HttpMsg *adapted)
{
    adapted->sources |= service().cfg().connectionEncryption ? HttpMsg::srcEcaps : HttpMsg::srcEcap;

    // Update masterXaction object for adapted HTTP requests.
    if (HttpRequest *adaptedReq = dynamic_cast<HttpRequest*>(adapted)) {
        HttpRequest *request = dynamic_cast<HttpRequest*> (theCauseRep ?
                               theCauseRep->raw().header : theVirginRep.raw().header);
        Must(request);
        adaptedReq->masterXaction = request->masterXaction;
    }
}