void Adaptation::Icap::Xaction::tellQueryAborted()
{
    if (theInitiator.set()) {
        Adaptation::Icap::XactAbortInfo abortInfo(icapRequest, icapReply,
                retriable(), repeatable());
        Launcher *launcher = dynamic_cast<Launcher*>(theInitiator.get());
        // launcher may be nil if initiator is invalid
        CallJobHere1(91,5, CbcPointer<Launcher>(launcher),
                     Launcher, noteXactAbort, abortInfo);
        clearInitiator();
    }
}