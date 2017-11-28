void
Adaptation::Ecap::XactionRep::start()
{
    Must(theMaster);

    if (!theVirginRep.raw().body_pipe)
        makingVb = opNever; // there is nothing to deliver

    HttpRequest *request = dynamic_cast<HttpRequest*> (theCauseRep ?
                           theCauseRep->raw().header : theVirginRep.raw().header);
    Must(request);

    HttpReply *reply = dynamic_cast<HttpReply*>(theVirginRep.raw().header);

    Adaptation::History::Pointer ah = request->adaptLogHistory();
    if (ah != NULL) {
        // retrying=false because ecap never retries transactions
        adaptHistoryId = ah->recordXactStart(service().cfg().key, current_time, false);
        typedef Notes::iterator ACAMLI;
        for (ACAMLI i = Adaptation::Config::metaHeaders.begin(); i != Adaptation::Config::metaHeaders.end(); ++i) {
            const char *v = (*i)->match(request, reply);
            if (v) {
                if (ah->metaHeaders == NULL)
                    ah->metaHeaders = new NotePairs();
                if (!ah->metaHeaders->hasPair((*i)->key.termedBuf(), v))
                    ah->metaHeaders->add((*i)->key.termedBuf(), v);
            }
        }
    }

    theMaster->start();
}