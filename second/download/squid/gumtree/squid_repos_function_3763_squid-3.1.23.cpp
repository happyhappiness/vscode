void Adaptation::Initiate::tellQueryAborted(bool final)
{
    CallJobHere1(93, 5, theInitiator,
                 Initiator, noteAdaptationQueryAbort, final);
    clearInitiator();
}