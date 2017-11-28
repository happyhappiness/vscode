void Adaptation::Iterator::step()
{
    ++iterations;
    debugs(93,5, HERE << '#' << iterations << " plan: " << thePlan);

    Must(!theLauncher);

    if (thePlan.exhausted()) { // nothing more to do
        sendAnswer(Answer::Forward(theMsg));
        Must(done());
        return;
    }

    HttpRequest *request = dynamic_cast<HttpRequest*>(theMsg);
    if (!request)
        request = theCause;
    assert(request);
    request->clearError();

    if (iterations > Adaptation::Config::service_iteration_limit) {
        debugs(93,DBG_CRITICAL, "Adaptation iterations limit (" <<
               Adaptation::Config::service_iteration_limit << ") exceeded:\n" <<
               "\tPossible service loop with " <<
               theGroup->kind << " " << theGroup->id << ", plan=" << thePlan);
        throw TexcHere("too many adaptations");
    }

    ServicePointer service = thePlan.current();
    Must(service != NULL);
    debugs(93,5, HERE << "using adaptation service: " << service->cfg().key);

    if (Adaptation::Config::needHistory) {
        Adaptation::History::Pointer ah = request->adaptHistory(true);
        auto uid = StringToSBuf(thePlan.current()->cfg().key);
        ah->recordAdaptationService(uid);
    }

    theLauncher = initiateAdaptation(
                      service->makeXactLauncher(theMsg, theCause, al));
    Must(initiated(theLauncher));
    Must(!done());
}