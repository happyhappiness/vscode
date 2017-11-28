void Adaptation::Icap::ModXact::prepPartialBodyEchoing(uint64_t pos)
{
    Must(virginBodySending.active());
    Must(virgin.header->body_pipe != NULL);

    setOutcome(xoPartEcho);

    debugs(93, 7, HERE << "will echo virgin body suffix from " <<
           virgin.header->body_pipe << " offset " << pos );

    // check that use-original-body=N does not point beyond buffered data
    const uint64_t virginDataEnd = virginConsumed +
                                   virgin.body_pipe->buf().contentSize();
    Must(pos <= virginDataEnd);
    virginBodySending.progress(static_cast<size_t>(pos));

    state.sending = State::sendingVirgin;
    checkConsuming();

    if (virgin.header->body_pipe->bodySizeKnown())
        adapted.body_pipe->expectProductionEndAfter(virgin.header->body_pipe->bodySize() - pos);

    debugs(93, 7, HERE << "will echo virgin body suffix to " <<
           adapted.body_pipe);

    // Start echoing data
    echoMore();
}