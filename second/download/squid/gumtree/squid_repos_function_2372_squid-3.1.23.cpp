bool
StoreMetaUnpacker::doOneEntry()
{
    getType();
    getLength();

    if (position + length > *hdr_len) {
        debugs(20, 0, "storeSwapMetaUnpack: overflow!");
        debugs(20, 0, "\ttype=" << type << ", length=" << length << ", *hdr_len=" << *hdr_len << ", offset=" << position);
        return false;
    }

    StoreMeta *newNode = StoreMeta::Factory(type, length, &buf[position]);

    if (newNode)
        tail = StoreMeta::Add (tail, newNode);

    position += length;

    return true;
}