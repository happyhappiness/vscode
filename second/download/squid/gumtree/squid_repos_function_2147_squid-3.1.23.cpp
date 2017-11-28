void ServerStateData::handleAdaptedBodyProducerAborted()
{
    stopConsumingFrom(adaptedBodySource);
    handleAdaptationAborted();
}