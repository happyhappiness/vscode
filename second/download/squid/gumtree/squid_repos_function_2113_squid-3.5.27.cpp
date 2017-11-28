size_t
BodyPipe::putMoreData(const char *aBuffer, size_t size)
{
    if (bodySizeKnown())
        size = min((uint64_t)size, unproducedSize());

    const size_t spaceSize = static_cast<size_t>(theBuf.potentialSpaceSize());
    if ((size = min(size, spaceSize))) {
        theBuf.append(aBuffer, size);
        postAppend(size);
        return size;
    }
    return 0;
}