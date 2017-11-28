void Adaptation::Icap::ModXact::parseMore()
{
    debugs(93, 5, HERE << "have " << readBuf.contentSize() << " bytes to parse" <<
           status());
    debugs(93, 5, HERE << "\n" << readBuf.content());

    if (state.parsingHeaders())
        parseHeaders();

    if (state.parsing == State::psBody)
        parseBody();
}