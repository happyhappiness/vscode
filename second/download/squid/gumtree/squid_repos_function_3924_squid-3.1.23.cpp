void Adaptation::Icap::ModXact::stopParsing()
{
    if (state.parsing == State::psDone)
        return;

    debugs(93, 7, HERE << "will no longer parse" << status());

    delete bodyParser;

    bodyParser = NULL;

    state.parsing = State::psDone;
}