bool
StoreMetaUnpacker::moreToProcess() const
{
    return *hdr_len - position - MinimumBufferLength >= 0;
}