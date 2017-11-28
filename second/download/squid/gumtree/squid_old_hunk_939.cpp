
void Adaptation::Icap::ModXact::parseBody()
{
    Must(state.parsing == State::psBody);
    Must(bodyParser);

    debugs(93, 5, HERE << "have " << readBuf.contentSize() << " body bytes to parse");

    // the parser will throw on errors
    BodyPipeCheckout bpc(*adapted.body_pipe);
    const bool parsed = bodyParser->parse(&readBuf, &bpc.buf);
    bpc.checkIn();

    debugs(93, 5, HERE << "have " << readBuf.contentSize() << " body bytes after " <<
           "parse; parsed all: " << parsed);
    replyHttpBodySize += adapted.body_pipe->buf().contentSize();

    // TODO: expose BodyPipe::putSize() to make this check simpler and clearer
    // TODO: do we really need this if we disable when sending headers?
    if (adapted.body_pipe->buf().contentSize() > 0) { // parsed something sometime
        disableRepeats("sent adapted content");
