void
ServerStateData::handleMoreAdaptedBodyAvailable()
{
    if (abortOnBadEntry("entry refuses adapted body"))
        return;

    assert(entry);

    size_t contentSize = adaptedBodySource->buf().contentSize();

    if (!contentSize)
        return; // XXX: bytesWanted asserts on zero-size ranges

    const size_t spaceAvailable = entry->bytesWanted(Range<size_t>(0, contentSize), true);

    if (spaceAvailable < contentSize ) {
        // No or partial body data consuming
        typedef NullaryMemFunT<ServerStateData> Dialer;
        AsyncCall::Pointer call = asyncCall(93, 5, "ServerStateData::resumeBodyStorage",
                                            Dialer(this, &ServerStateData::resumeBodyStorage));
        entry->deferProducer(call);
    }

    if (!spaceAvailable)  {
        debugs(11, 5, HERE << "NOT storing " << contentSize << " bytes of adapted " <<
               "response body at offset " << adaptedBodySource->consumedSize());
        return;
    }

    if (spaceAvailable < contentSize ) {
        debugs(11, 5, HERE << "postponing storage of " <<
               (contentSize - spaceAvailable) << " body bytes");
        contentSize = spaceAvailable;
    }

    debugs(11,5, HERE << "storing " << contentSize << " bytes of adapted " <<
           "response body at offset " << adaptedBodySource->consumedSize());

    BodyPipeCheckout bpc(*adaptedBodySource);
    const StoreIOBuffer ioBuf(&bpc.buf, currentOffset, contentSize);
    currentOffset += ioBuf.length;
    entry->write(ioBuf);
    bpc.buf.consume(contentSize);
    bpc.checkIn();
}