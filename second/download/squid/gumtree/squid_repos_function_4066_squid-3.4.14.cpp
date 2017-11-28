void Adaptation::Icap::ModXact::parseHeaders()
{
    Must(state.parsingHeaders());

    if (state.parsing == State::psIcapHeader) {
        debugs(93, 5, HERE << "parse ICAP headers");
        parseIcapHead();
    }

    if (state.parsing == State::psHttpHeader) {
        debugs(93, 5, HERE << "parse HTTP headers");
        parseHttpHead();
    }

    if (state.parsingHeaders()) { // need more data
        Must(mayReadMore());
        return;
    }

    startSending();
}