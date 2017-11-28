StoreMeta *
StoreMetaUnpacker::createStoreMeta ()
{
    tlv *TLV = NULL;
    tail = &TLV;
    assert(hdr_len != NULL);

    checkBuffer();

    getBufferLength();

    assert (position == 1 + sizeof(int));

    while (moreToProcess()) {
        if (!doOneEntry())
            break;
    }

    if (!TLV)
        throw TexcHere("store entry metadata is empty");

    assert(TLV);
    return TLV;
}