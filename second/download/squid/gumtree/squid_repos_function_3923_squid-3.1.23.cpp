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
    replyBodySize += adapted.body_pipe->buf().contentSize();

    // TODO: expose BodyPipe::putSize() to make this check simpler and clearer
    // TODO: do we really need this if we disable when sending headers?
    if (adapted.body_pipe->buf().contentSize() > 0) { // parsed something sometime
        disableRepeats("sent adapted content");
        disableBypass("sent adapted content", true);
    }

    if (parsed) {
        stopParsing();
        stopSending(true); // the parser succeeds only if all parsed data fits
        return;
    }

    debugs(93,3,HERE << this << " needsMoreData = " << bodyParser->needsMoreData());

    if (bodyParser->needsMoreData()) {
        debugs(93,3,HERE << this);
        Must(mayReadMore());
        readMore();
    }

    if (bodyParser->needsMoreSpace()) {
        Must(!doneSending()); // can hope for more space
        Must(adapted.body_pipe->buf().contentSize() > 0); // paranoid
        // TODO: there should be a timeout in case the sink is broken
        // or cannot consume partial content (while we need more space)
    }
}