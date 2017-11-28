bool
BodyProducerDialer::canDial(AsyncCall &call)
{
    if (!Parent::canDial(call))
        return false;

    const BodyProducer::Pointer &producer = job;
    BodyPipe::Pointer aPipe = arg1;
    if (!aPipe->stillProducing(producer)) {
        debugs(call.debugSection, call.debugLevel, producer << " no longer producing for " << aPipe->status());
        return call.cancel("no longer producing");
    }

    return true;
}