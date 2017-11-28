
// called after parsing all headers or when bypassing an exception
void Adaptation::Icap::ModXact::startSending()
{
    disableRepeats("sent headers");
    disableBypass("sent headers", true);
    sendAnswer(adapted.header);

    if (state.sending == State::sendingVirgin)
        echoMore();
}

void Adaptation::Icap::ModXact::parseIcapHead()
