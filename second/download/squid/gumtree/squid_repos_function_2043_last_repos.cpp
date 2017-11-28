bool
StoreMetaUnpacker::isBufferZero()
{
    // We could memcmp the entire buffer, but it is probably safe enough
    // to test a few bytes because if we do not detect a corrupted entry
    // it is not a big deal. Empty entries are not isBufferSane anyway.
    const int depth = 10;
    if (buflen < depth)
        return false; // cannot be sure enough

    for (int i = 0; i < depth; ++i) {
        if (buf[i])
            return false;
    }
    return true;
}