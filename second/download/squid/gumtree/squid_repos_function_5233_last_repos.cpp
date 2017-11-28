void
Client::endAdaptedBodyConsumption()
{
    stopConsumingFrom(adaptedBodySource);
    handleAdaptationCompleted();
}