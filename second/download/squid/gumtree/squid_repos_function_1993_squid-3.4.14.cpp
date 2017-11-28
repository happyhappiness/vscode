void
BodyPipe::clearConsumer()
{
    if (theConsumer.set()) {
        debugs(91,7, HERE << "clearing consumer" << status());
        theConsumer.clear();
        // do not abort if we have not consumed so that HTTP or ICAP can retry
        // benign xaction failures due to persistent connection race conditions
        if (consumedSize())
            expectNoConsumption();
    }
}