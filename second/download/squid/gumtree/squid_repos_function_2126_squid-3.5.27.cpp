void
BodyPipe::scheduleBodyDataNotification()
{
    if (theConsumer.valid()) { // TODO: allow asyncCall() to check this instead
        AsyncCall::Pointer call = asyncCall(91, 7,
                                            "BodyConsumer::noteMoreBodyDataAvailable",
                                            BodyConsumerDialer(theConsumer,
                                                    &BodyConsumer::noteMoreBodyDataAvailable, this));
        ScheduleCallHere(call);
    }
}