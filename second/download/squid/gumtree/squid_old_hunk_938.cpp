    disableRepeats("sent headers");
    disableBypass("sent headers", true);
    sendAnswer(Answer::Forward(adapted.header));

    if (state.sending == State::sendingVirgin)
        echoMore();
}

void Adaptation::Icap::ModXact::parseIcapHead()
{
    Must(state.sending == State::sendingUndecided);

