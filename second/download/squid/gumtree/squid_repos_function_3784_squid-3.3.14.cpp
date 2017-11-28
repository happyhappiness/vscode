Adaptation::ServiceFilter Adaptation::Iterator::filter() const
{
    // the method may differ from theGroup->method due to request satisfaction
    Method method = methodNone;
    // temporary variables, no locking needed
    HttpRequest *req = NULL;
    HttpReply *rep = NULL;

    if (HttpRequest *r = dynamic_cast<HttpRequest*>(theMsg)) {
        method = methodReqmod;
        req = r;
        rep = NULL;
    } else if (HttpReply *theReply = dynamic_cast<HttpReply*>(theMsg)) {
        method = methodRespmod;
        req = theCause;
        rep = theReply;
    } else {
        Must(false); // should not happen
    }

    return ServiceFilter(method, theGroup->point, req, rep);
}