void
Adaptation::Initiator::announceInitiatorAbort(CbcPointer<Initiate> &x)
{
    CallJobHere(93, 5, x, Initiate, noteInitiatorAborted);
    clearAdaptation(x);
}