bool
MemObject::readAheadPolicyCanRead() const
{
    const bool canRead = endOffset() - getReply()->hdr_sz <
                         lowestMemReaderOffset() + Config.readAheadGap;

    if (!canRead) {
        debugs(19, 9, "no: " << endOffset() << '-' << getReply()->hdr_sz <<
               " < " << lowestMemReaderOffset() << '+' << Config.readAheadGap);
    }

    return canRead;
}