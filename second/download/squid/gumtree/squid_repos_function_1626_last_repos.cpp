const char *BodyPipe::status() const
{
    static MemBuf outputBuffer;
    outputBuffer.reset();

    outputBuffer.append(" [", 2);

    outputBuffer.appendf("%" PRIu64 "<=%" PRIu64, theGetSize, thePutSize);
    if (theBodySize >= 0)
        outputBuffer.appendf("<=%" PRId64, theBodySize);
    else
        outputBuffer.append("<=?", 3);

    outputBuffer.appendf(" %" PRId64 "+%" PRId64, static_cast<int64_t>(theBuf.contentSize()), static_cast<int64_t>(theBuf.spaceSize()));

    outputBuffer.appendf(" pipe%p", this);
    if (theProducer.set())
        outputBuffer.appendf(" prod%p", theProducer.get());
    if (theConsumer.set())
        outputBuffer.appendf(" cons%p", theConsumer.get());

    if (mustAutoConsume)
        outputBuffer.append(" A", 2);
    if (abortedConsumption)
        outputBuffer.append(" !C", 3);
    if (isCheckedOut)
        outputBuffer.append(" L", 2); // Locked

    outputBuffer.append("]", 1);

    outputBuffer.terminate();

    return outputBuffer.content();
}