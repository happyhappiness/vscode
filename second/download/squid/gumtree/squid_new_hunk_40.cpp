    if (theLaunches >= TheConfig.repeat_limit)
        x->disableRepeats("over icap_retry_limit");
    theXaction = initiateAdaptation(x);
    Must(initiated(theXaction));
}

void Adaptation::Icap::Launcher::noteAdaptationAnswer(const Answer &answer)
{
    debugs(93,5, HERE << "launches: " << theLaunches << " answer: " << answer);

    // XXX: akError is unused by ICAPXaction in favor of noteXactAbort()
    Must(answer.kind != Answer::akError);

    sendAnswer(answer);
    clearAdaptation(theXaction);
    Must(done());
}

void Adaptation::Icap::Launcher::noteInitiatorAborted()
{

    announceInitiatorAbort(theXaction); // propogate to the transaction
    clearInitiator();
    Must(done()); // should be nothing else to do

}

void Adaptation::Icap::Launcher::noteXactAbort(XactAbortInfo info)
{
    debugs(93,5, HERE << "theXaction:" << theXaction << " launches: " << theLaunches);

    // TODO: add more checks from FwdState::checkRetry()?
    if (canRetry(info)) {
