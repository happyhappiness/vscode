void Adaptation::Iterator::handleAdaptationError(bool final)
{
    debugs(93,5, HERE << "final: " << final << " plan: " << thePlan);
    clearAdaptation(theLauncher);
    updatePlan(false);

    // can we replace the failed service (group-level bypass)?
    const bool srcIntact = !theMsg->body_pipe ||
                           !theMsg->body_pipe->consumedSize();
    // can we ignore the failure (compute while thePlan is not exhausted)?
    Must(!thePlan.exhausted());
    const bool canIgnore = thePlan.current()->cfg().bypass;
    debugs(85,5, HERE << "flags: " << srcIntact << canIgnore << adapted);

    if (srcIntact) {
        if (thePlan.replacement(filter()) != NULL) {
            debugs(93,3, HERE << "trying a replacement service");
            step();
            return;
        }
    }

    if (canIgnore && srcIntact && adapted) {
        debugs(85,3, HERE << "responding with older adapted msg");
        sendAnswer(Answer::Forward(theMsg));
        mustStop("sent older adapted msg");
        return;
    }

    // caller may recover if we can ignore the error and virgin msg is intact
    const bool useVirgin = canIgnore && !adapted && srcIntact;
    tellQueryAborted(!useVirgin);
    mustStop("group failure");
}