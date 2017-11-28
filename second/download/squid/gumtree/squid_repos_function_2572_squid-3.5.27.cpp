bool
StoreMetaUnpacker::doOneEntry()
{
    getType();
    getLength();

    if (position + length > *hdr_len) {
        debugs(20, DBG_CRITICAL, "storeSwapMetaUnpack: overflow!");
        debugs(20, DBG_CRITICAL, "\ttype=" << type << ", length=" << length << ", *hdr_len=" << *hdr_len << ", offset=" << position);
        return false;
    }

    StoreMeta *newNode = StoreMeta::Factory(type, length, &buf[position]);

    if (newNode)
        tail = StoreMeta::Add (tail, newNode);

    position += length;

    return true;
}