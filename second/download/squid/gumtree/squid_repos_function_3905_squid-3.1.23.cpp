void Adaptation::Icap::ModXact::checkConsuming()
{
    // quit if we already stopped or are still using the pipe
    if (!virgin.body_pipe || !state.doneConsumingVirgin())
        return;

    debugs(93, 7, HERE << "will stop consuming" << status());
    stopConsumingFrom(virgin.body_pipe);
}