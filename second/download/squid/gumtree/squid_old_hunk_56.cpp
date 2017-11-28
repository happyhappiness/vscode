{
    return !writer;
}

bool Adaptation::Icap::Xaction::doneWithIo() const
{
    return connection >= 0 && // or we could still be waiting to open it
           !connector && !reader && !writer && // fast checks, some redundant
           doneReading() && doneWriting();
}

// initiator aborted
void Adaptation::Icap::Xaction::noteInitiatorAborted()
{

    if (theInitiator.set()) {
        clearInitiator();
        mustStop("initiator aborted");
    }

}

void Adaptation::Icap::Xaction::setOutcome(const Adaptation::Icap::XactOutcome &xo)
