void Adaptation::Icap::ModXact::echoMore()
{
    Must(state.sending == State::sendingVirgin);
    Must(adapted.body_pipe != NULL);
    Must(virginBodySending.active());

    const size_t sizeMax = virginContentSize(virginBodySending);
    debugs(93,5, HERE << "will echo up to " << sizeMax << " bytes from " <<
           virgin.body_pipe->status());
    debugs(93,5, HERE << "will echo up to " << sizeMax << " bytes to   " <<
           adapted.body_pipe->status());

    if (sizeMax > 0) {
        const size_t size = adapted.body_pipe->putMoreData(virginContentData(virginBodySending), sizeMax);
        debugs(93,5, HERE << "echoed " << size << " out of " << sizeMax <<
               " bytes");
        virginBodySending.progress(size);
        disableRepeats("echoed content");
        disableBypass("echoed content", true);
        virginConsume();
    }

    if (virginBodyEndReached(virginBodySending)) {
        debugs(93, 5, HERE << "echoed all" << status());
        stopSending(true);
    } else {
        debugs(93, 5, HERE << "has " <<
               virgin.body_pipe->buf().contentSize() << " bytes " <<
               "and expects more to echo" << status());
        // TODO: timeout if virgin or adapted pipes are broken
    }
}