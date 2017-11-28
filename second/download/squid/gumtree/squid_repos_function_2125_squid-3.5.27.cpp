void
BodyPipe::postAppend(size_t size)
{
    assert(!isCheckedOut);
    thePutSize += size;
    debugs(91,7, HERE << "added " << size << " bytes" << status());

    if (mustAutoConsume && !theConsumer && size > 0)
        startAutoConsumption();

    // We should not consume here even if mustAutoConsume because the
    // caller may not be ready for the data to be consumed during this call.
    scheduleBodyDataNotification();

    if (!mayNeedMoreData())
        clearProducer(true); // reached end-of-body
}