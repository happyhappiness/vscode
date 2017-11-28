void Adaptation::Iterator::noteAdaptationAnswer(HttpMsg *aMsg)
{
    // set theCause if we switched to request satisfaction mode
    if (!theCause) { // probably sent a request message
        if (dynamic_cast<HttpReply*>(aMsg)) { // we got a response message
            if (HttpRequest *cause = dynamic_cast<HttpRequest*>(theMsg)) {
                // definately sent request, now use it as the cause
                theCause = cause; // moving the lock
                theMsg = 0;
                debugs(93,3, HERE << "in request satisfaction mode");
            }
        }
    }

    Must(aMsg);
    HTTPMSGUNLOCK(theMsg);
    theMsg = HTTPMSGLOCK(aMsg);
    adapted = true;

    clearAdaptation(theLauncher);
    if (!updatePlan(true)) // do not immediatelly advance the new plan
        thePlan.next(filter());
    step();
}