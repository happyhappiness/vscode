bool
BodyPipe::setConsumerIfNotLate(const Consumer::Pointer &aConsumer)
{
    assert(!theConsumer);
    assert(aConsumer.set()); // but might be invalid

    // TODO: convert this into an exception and remove IfNotLate suffix
    // If there is something consumed already, we are in an auto-consuming mode
    // and it is too late to attach a real consumer to the pipe.
    if (theGetSize > 0) {
        assert(mustAutoConsume);
        return false;
    }

    Must(!abortedConsumption); // did not promise to never consume

    theConsumer = aConsumer;
    debugs(91,7, HERE << "set consumer" << status());
    if (theBuf.hasContent())
        scheduleBodyDataNotification();
    if (!theProducer)
        scheduleBodyEndNotification();

    return true;
}