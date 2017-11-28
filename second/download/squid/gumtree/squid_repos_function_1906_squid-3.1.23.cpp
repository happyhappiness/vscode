bool
BodyProducerDialer::canDial(AsyncCall &call)
{
    if (!Parent::canDial(call))
        return false;

    const BodyProducer::Pointer &producer = job;
    BodyPipe::Pointer pipe = arg1;
    if (!pipe->stillProducing(producer)) {
        debugs(call.debugSection, call.debugLevel, HERE << producer <<
               " no longer producing for " << pipe->status());
        return call.cancel("no longer producing");
    }

    return true;
}