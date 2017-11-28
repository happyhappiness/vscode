void
BodyPipe::scheduleBodyEndNotification()
{
    if (theConsumer.valid()) { // TODO: allow asyncCall() to check this instead
        if (bodySizeKnown() && bodySize() == thePutSize) {
            AsyncCall::Pointer call = asyncCall(91, 7,
                                                "BodyConsumer::noteBodyProductionEnded",
                                                BodyConsumerDialer(theConsumer,
                                                        &BodyConsumer::noteBodyProductionEnded, this));
            ScheduleCallHere(call);
        } else {
            AsyncCall::Pointer call = asyncCall(91, 7,
                                                "BodyConsumer::noteBodyProducerAborted",
                                                BodyConsumerDialer(theConsumer,
                                                        &BodyConsumer::noteBodyProducerAborted, this));
            ScheduleCallHere(call);
        }
    }
}