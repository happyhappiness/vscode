size_t
BodyPipe::getMoreData(MemBuf &aMemBuffer)
{
    if (!theBuf.hasContent())
        return 0; // did not touch the possibly uninitialized buf

    if (aMemBuffer.isNull())
        aMemBuffer.init();
    const size_t size = min(theBuf.contentSize(), aMemBuffer.potentialSpaceSize());
    aMemBuffer.append(theBuf.content(), size);
    theBuf.consume(size);
    postConsume(size);
    return size; // cannot be zero if we called buf.init above
}