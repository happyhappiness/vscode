void Adaptation::Icap::ModXact::handle200Ok()
{
    state.parsing = State::psHttpHeader;
    state.sending = State::sendingAdapted;
    stopBackup();
    checkConsuming();
}