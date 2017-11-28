void
ClientHttpRequest::noteMoreBodyDataAvailable(BodyPipe::Pointer)
{
    assert(request_satisfaction_mode);
    assert(adaptedBodySource != NULL);

    if (size_t contentSize = adaptedBodySource->buf().contentSize()) {
        const size_t spaceAvailable = storeEntry()->bytesWanted(Range<size_t>(0,contentSize));

        if (spaceAvailable < contentSize ) {
            // No or partial body data consuming
            typedef NullaryMemFunT<ClientHttpRequest> Dialer;
            AsyncCall::Pointer call = asyncCall(93, 5, "ClientHttpRequest::resumeBodyStorage",
                                                Dialer(this, &ClientHttpRequest::resumeBodyStorage));
            storeEntry()->deferProducer(call);
        }

        if (!spaceAvailable)
            return;

        if (spaceAvailable < contentSize )
            contentSize = spaceAvailable;

        BodyPipeCheckout bpc(*adaptedBodySource);
        const StoreIOBuffer ioBuf(&bpc.buf, request_satisfaction_offset, contentSize);
        storeEntry()->write(ioBuf);
        // assume StoreEntry::write() writes the entire ioBuf
        request_satisfaction_offset += ioBuf.length;
        bpc.buf.consume(contentSize);
        bpc.checkIn();
    }

    if (adaptedBodySource->exhausted())
        endRequestSatisfaction();
    // else wait for more body data
}