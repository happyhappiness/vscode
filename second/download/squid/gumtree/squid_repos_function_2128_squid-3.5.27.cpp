const char *BodyPipe::status() const
{
    static MemBuf outputBuffer;
    outputBuffer.reset();

    outputBuffer.append(" [", 2);

    outputBuffer.Printf("%" PRIu64 "<=%" PRIu64, theGetSize, thePutSize);
    if (theBodySize >= 0)
        outputBuffer.Printf("<=%" PRId64, theBodySize);
    else
        outputBuffer.append("<=?", 3);

    outputBuffer.Printf(" %d+%d", (int)theBuf.contentSize(), (int)theBuf.spaceSize());

    outputBuffer.Printf(" pipe%p", this);
    if (theProducer.set())
        outputBuffer.Printf(" prod%p", theProducer.get());
    if (theConsumer.set())
        outputBuffer.Printf(" cons%p", theConsumer.get());

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