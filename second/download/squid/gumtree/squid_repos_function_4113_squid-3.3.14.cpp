void Adaptation::Icap::Launcher::noteXactAbort(XactAbortInfo info)
{
    debugs(93,5, HERE << "theXaction:" << theXaction << " launches: " << theLaunches);

    // TODO: add more checks from FwdState::checkRetry()?
    if (canRetry(info)) {
        clearAdaptation(theXaction);
        launchXaction("retry");
    } else if (canRepeat(info)) {
        clearAdaptation(theXaction);
        launchXaction("repeat");
    } else {
        debugs(93,3, HERE << "cannot retry or repeat a failed transaction");
        clearAdaptation(theXaction);
        tellQueryAborted(false); // caller decides based on bypass, consumption
        Must(done());
    }
}