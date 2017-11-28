void BodyPipe::expectProductionEndAfter(uint64_t size)
{
    const uint64_t expectedSize = thePutSize + size;
    if (bodySizeKnown())
        Must(bodySize() == expectedSize);
    else
        theBodySize = expectedSize;
}