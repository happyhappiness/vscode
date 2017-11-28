bool Adaptation::Icap::ModXact::doneAll() const
{
    return Adaptation::Icap::Xaction::doneAll() && !state.serviceWaiting &&
           doneSending() &&
           doneReading() && state.doneWriting();
}