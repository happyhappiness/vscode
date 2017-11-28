void Adaptation::Icap::ModXact::parseMore()
{
    debugs(93, 5, "have " << readBuf.length() << " bytes to parse" << status());
    debugs(93, 5, "\n" << readBuf);

    if (state.parsingHeaders())
        parseHeaders();

    if (state.parsing == State::psBody)
        parseBody();
}