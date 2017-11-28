bool Adaptation::Icap::ModXact::doneSending() const
{
    return state.sending == State::sendingDone;
}