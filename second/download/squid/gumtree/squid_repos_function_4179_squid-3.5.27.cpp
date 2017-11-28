void Adaptation::Icap::ModXact::estimateVirginBody()
{
    // note: lack of size info may disable previews and 204s

    HttpMsg *msg = virgin.header;
    Must(msg);

    HttpRequestMethod method;

    if (virgin.cause)
        method = virgin.cause->method;
    else if (HttpRequest *req = dynamic_cast<HttpRequest*>(msg))
        method = req->method;
    else
        method = Http::METHOD_NONE;

    int64_t size;
    // expectingBody returns true for zero-sized bodies, but we will not
    // get a pipe for that body, so we treat the message as bodyless
    if (method != Http::METHOD_NONE && msg->expectingBody(method, size) && size) {
        debugs(93, 6, HERE << "expects virgin body from " <<
               virgin.body_pipe << "; size: " << size);

        virginBody.expect(size);
        virginBodyWriting.plan();

        // sign up as a body consumer
        Must(msg->body_pipe != NULL);
        Must(msg->body_pipe == virgin.body_pipe);
        Must(virgin.body_pipe->setConsumerIfNotLate(this));

        // make sure TheBackupLimit is in-sync with the buffer size
        Must(TheBackupLimit <= static_cast<size_t>(msg->body_pipe->buf().max_capacity));
    } else {
        debugs(93, 6, HERE << "does not expect virgin body");
        Must(msg->body_pipe == NULL);
        checkConsuming();
    }
}