void BodyPipe::setBodySize(uint64_t aBodySize)
{
    assert(!bodySizeKnown());
    assert(thePutSize <= aBodySize);

    // If this assert fails, we need to add code to check for eof and inform
    // the consumer about the eof condition via scheduleBodyEndNotification,
    // because just setting a body size limit may trigger the eof condition.
    assert(!theConsumer);

    theBodySize = aBodySize;
    debugs(91,7, HERE << "set body size" << status());
}