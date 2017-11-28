bool
Adaptation::AccessCheck::Start(Method method, VectPoint vp,
                               HttpRequest *req, HttpReply *rep, Adaptation::Initiator *initiator)
{

    if (Config::Enabled) {
        // the new check will call the callback and delete self, eventually
        AsyncJob::Start(new AccessCheck( // we do not store so not a CbcPointer
                            ServiceFilter(method, vp, req, rep), initiator));
        return true;
    }

    debugs(83, 3, HERE << "adaptation off, skipping");
    return false;
}