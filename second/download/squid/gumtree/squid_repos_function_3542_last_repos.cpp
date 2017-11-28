void Adaptation::Icap::ModXact::prepEchoing()
{
    disableRepeats("preparing to echo content");
    disableBypass("preparing to echo content", true);
    setOutcome(xoEcho);

    // We want to clone the HTTP message, but we do not want
    // to copy some non-HTTP state parts that HttpMsg kids carry in them.
    // Thus, we cannot use a smart pointer, copy constructor, or equivalent.
    // Instead, we simply write the HTTP message and "clone" it by parsing.
    // TODO: use HttpMsg::clone()!

    HttpMsg *oldHead = virgin.header;
    debugs(93, 7, HERE << "cloning virgin message " << oldHead);

    MemBuf httpBuf;

    // write the virgin message into a memory buffer
    httpBuf.init();
    packHead(httpBuf, oldHead);

    // allocate the adapted message and copy metainfo
    Must(!adapted.header);
    {
        HttpMsg::Pointer newHead;
        if (const HttpRequest *r = dynamic_cast<const HttpRequest*>(oldHead)) {
            newHead = new HttpRequest(r->masterXaction);
        } else if (dynamic_cast<const HttpReply*>(oldHead)) {
            newHead = new HttpReply;
        }
        Must(newHead);

        newHead->inheritProperties(oldHead);

        adapted.setHeader(newHead.getRaw());
    }

    // parse the buffer back
    Http::StatusCode error = Http::scNone;

    httpBuf.terminate(); // HttpMsg::parse requires nil-terminated buffer
    Must(adapted.header->parse(httpBuf.content(), httpBuf.contentSize(), true, &error));
    Must(adapted.header->hdr_sz == httpBuf.contentSize()); // no leftovers

    httpBuf.clean();

    debugs(93, 7, HERE << "cloned virgin message " << oldHead << " to " <<
           adapted.header);

    // setup adapted body pipe if needed
    if (oldHead->body_pipe != NULL) {
        debugs(93, 7, HERE << "will echo virgin body from " <<
               oldHead->body_pipe);
        if (!virginBodySending.active())
            virginBodySending.plan(); // will throw if not possible
        state.sending = State::sendingVirgin;
        checkConsuming();

        // TODO: optimize: is it possible to just use the oldHead pipe and
        // remove ICAP from the loop? This echoing is probably a common case!
        makeAdaptedBodyPipe("echoed virgin response");
        if (oldHead->body_pipe->bodySizeKnown())
            adapted.body_pipe->setBodySize(oldHead->body_pipe->bodySize());
        debugs(93, 7, HERE << "will echo virgin body to " <<
               adapted.body_pipe);
    } else {
        debugs(93, 7, HERE << "no virgin body to echo");
        stopSending(true);
    }
}