void Adaptation::Icap::ModXact::stopSending(bool nicely)
{
    debugs(93, 7, HERE << "Enter stop sending ");
    if (doneSending())
        return;
    debugs(93, 7, HERE << "Proceed with stop sending ");

    if (state.sending != State::sendingUndecided) {
        debugs(93, 7, HERE << "will no longer send" << status());
        if (adapted.body_pipe != NULL) {
            virginBodySending.disable();
            // we may leave debts if we were echoing and the virgin
            // body_pipe got exhausted before we echoed all planned bytes
            const bool leftDebts = adapted.body_pipe->needsMoreData();
            stopProducingFor(adapted.body_pipe, nicely && !leftDebts);
        }
    } else {
        debugs(93, 7, HERE << "will not start sending" << status());
        Must(!adapted.body_pipe);
    }

    state.sending = State::sendingDone;
    checkConsuming();
}