void Adaptation::Iterator::noteInitiatorAborted()
{
    announceInitiatorAbort(theLauncher); // propogate to the transaction
    clearInitiator();
    mustStop("initiator gone");
}