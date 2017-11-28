bool
BodyConsumerDialer::canDial(AsyncCall &call)
{
    if (!Parent::canDial(call))
        return false;

    const BodyConsumer::Pointer &consumer = job;
    BodyPipe::Pointer pipe = arg1;
    if (!pipe->stillConsuming(consumer)) {
        debugs(call.debugSection, call.debugLevel, HERE << consumer <<
               " no longer consuming from " << pipe->status());
        return call.cancel("no longer consuming");
    }

    return true;
}