void
BodyPipe::enableAutoConsumption()
{
    mustAutoConsume = true;
    debugs(91,5, HERE << "enabled auto consumption" << status());
    if (!theConsumer && theBuf.hasContent())
        startAutoConsumption();
}