void Adaptation::Icap::ModXact::decideOnParsingBody()
{
    if (gotEncapsulated("res-body") || gotEncapsulated("req-body")) {
        debugs(93, 5, HERE << "expecting a body");
        state.parsing = State::psBody;
        replyHttpBodySize = 0;
        bodyParser = new ChunkedCodingParser;
        makeAdaptedBodyPipe("adapted response from the ICAP server");
        Must(state.sending == State::sendingAdapted);
    } else {
        debugs(93, 5, HERE << "not expecting a body");
        stopParsing();
        stopSending(true);
    }
}