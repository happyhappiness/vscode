void Adaptation::Icap::ModXact::noteBodyProductionEnded(BodyPipe::Pointer)
{
    Must(virgin.body_pipe->productionEnded());

    // push writer and sender in case we were waiting for the last-chunk
    writeMore();

    if (state.sending == State::sendingVirgin)
        echoMore();
}