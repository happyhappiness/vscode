void
BodyPipe::postConsume(size_t size)
{
    assert(!isCheckedOut);
    theGetSize += size;
    debugs(91,7, HERE << "consumed " << size << " bytes" << status());
    if (mayNeedMoreData()) {
        AsyncCall::Pointer call=  asyncCall(91, 7,
                                            "BodyProducer::noteMoreBodySpaceAvailable",
                                            BodyProducerDialer(theProducer,
                                                    &BodyProducer::noteMoreBodySpaceAvailable, this));
        ScheduleCallHere(call);
    }
}