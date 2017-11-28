void Adaptation::Icap::ModXact::noteMoreBodyDataAvailable(BodyPipe::Pointer)
{
    writeMore();

    if (state.sending == State::sendingVirgin)
        echoMore();
}