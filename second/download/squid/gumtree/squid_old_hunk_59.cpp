{
    announceInitiatorAbort(theLauncher); // propogate to the transaction
    clearInitiator();
    mustStop("initiator gone");
}

void Adaptation::Iterator::noteAdaptationQueryAbort(bool final)
{
    debugs(93,5, HERE << "final: " << final << " plan: " << thePlan);
    clearAdaptation(theLauncher);
    updatePlan(false);

    // can we replace the failed service (group-level bypass)?
