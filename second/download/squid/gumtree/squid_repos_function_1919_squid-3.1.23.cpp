void
BodyPipe::expectNoConsumption()
{
    Must(!theConsumer);
    if (!abortedConsumption && !exhausted()) {
        AsyncCall::Pointer call= asyncCall(91, 7,
                                           "BodyProducer::noteBodyConsumerAborted",
                                           BodyProducerDialer(theProducer,
                                                              &BodyProducer::noteBodyConsumerAborted, this));
        ScheduleCallHere(call);
        abortedConsumption = true;
    }
}