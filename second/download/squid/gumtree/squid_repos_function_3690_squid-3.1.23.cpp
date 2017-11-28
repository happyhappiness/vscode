void Adaptation::Iterator::step()
{
    ++iterations;
    debugs(93,5, HERE << '#' << iterations << " plan: " << thePlan);

    Must(!theLauncher);

    if (thePlan.exhausted()) { // nothing more to do
        sendAnswer(theMsg);
        Must(done());
        return;
    }

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

    theLauncher = initiateAdaptation(
                      service->makeXactLauncher(theMsg, theCause));
    Must(initiated(theLauncher));
    Must(!done());
}