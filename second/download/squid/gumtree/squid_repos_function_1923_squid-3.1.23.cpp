void
BodyPipe::startAutoConsumption()
{
    Must(mustAutoConsume);
    Must(!theConsumer);
    theConsumer = new BodySink;
    debugs(91,7, HERE << "starting auto consumption" << status());
    scheduleBodyDataNotification();
}