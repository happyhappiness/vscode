void Adaptation::Icap::ModXact::noteMoreBodySpaceAvailable(BodyPipe::Pointer)
{
    if (state.sending == State::sendingVirgin)
        echoMore();
    else if (state.sending == State::sendingAdapted)
        parseMore();
    else
        Must(state.sending == State::sendingUndecided);
}