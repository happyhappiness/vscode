void
BodyPipe::expectNoConsumption()
{
    // We may be called multiple times because multiple jobs on the consumption
    // chain may realize that there will be no more setConsumer() calls (e.g.,
    // consuming code and retrying code). It is both difficult and not really
    // necessary for them to coordinate their expectNoConsumption() calls.

    // As a consequence, we may be called when we are auto-consuming already.

    if (!abortedConsumption && !exhausted()) {
        // Before we abort, any regular consumption should be over and auto
        // consumption must not be started.
        Must(!theConsumer);

        AsyncCall::Pointer call= asyncCall(91, 7,
                                           "BodyProducer::noteBodyConsumerAborted",
                                           BodyProducerDialer(theProducer,
                                                   &BodyProducer::noteBodyConsumerAborted, this));
        ScheduleCallHere(call);
        abortedConsumption = true;

        // in case somebody enabled auto-consumption before regular one aborted
        if (mustAutoConsume)
            startAutoConsumption();
    }
}