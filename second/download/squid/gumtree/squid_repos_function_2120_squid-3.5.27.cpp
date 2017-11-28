void
BodyPipe::startAutoConsumption()
{
    Must(mustAutoConsume);
    Must(!theConsumer);
    theConsumer = new BodySink(this);
    debugs(91,7, HERE << "starting auto consumption" << status());
    scheduleBodyDataNotification();
}