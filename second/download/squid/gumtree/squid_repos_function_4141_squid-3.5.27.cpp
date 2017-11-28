void Adaptation::Icap::ModXact::startSending()
{
    disableRepeats("sent headers");
    disableBypass("sent headers", true);
    sendAnswer(Answer::Forward(adapted.header));

    if (state.sending == State::sendingVirgin)
        echoMore();
}