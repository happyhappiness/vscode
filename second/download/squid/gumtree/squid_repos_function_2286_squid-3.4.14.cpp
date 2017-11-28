void
ServerStateData::endAdaptedBodyConsumption()
{
    stopConsumingFrom(adaptedBodySource);
    handleAdaptationCompleted();
}