bool
MemObject::readAheadPolicyCanRead() const
{
    return endOffset() - getReply()->hdr_sz < lowestMemReaderOffset() + Config.readAheadGap;
}