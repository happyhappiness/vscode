bool
BodyConsumerDialer::canDial(AsyncCall &call)
{
    if (!Parent::canDial(call))
        return false;

    const BodyConsumer::Pointer &consumer = job;
    BodyPipe::Pointer aPipe = arg1;
    if (!aPipe->stillConsuming(consumer)) {
        debugs(call.debugSection, call.debugLevel, consumer << " no longer consuming from " << aPipe->status());
        return call.cancel("no longer consuming");
    }

    return true;
}