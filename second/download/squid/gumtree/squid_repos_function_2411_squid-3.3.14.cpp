StoreMeta *
StoreMetaUnpacker::createStoreMeta ()
{
    tlv *TLV = NULL;
    tail = &TLV;
    assert(hdr_len != NULL);

    if (!isBufferSane())
        return NULL;

    getBufferLength();

    assert (position == 1 + sizeof(int));

    while (moreToProcess()) {
        if (!doOneEntry())
            break;
    }

    return TLV;
}