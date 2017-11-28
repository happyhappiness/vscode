bool
StoreSwapLogHeader::sane() const
{
    SwapChecksum24 actualSum;
    actualSum.set(version, record_size, 0);
    if (checksum != actualSum)
        return false;

    return op == SWAP_LOG_VERSION && version >= 2 && record_size > 0;
}