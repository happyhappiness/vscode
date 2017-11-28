void
ServerStateData::noteBodyProductionEnded(BodyPipe::Pointer bp)
{
#if USE_ADAPTATION
    if (adaptedBodySource == bp) {
        handleAdaptedBodyProductionEnded();
        return;
    }
#endif
    if (requestBodySource == bp)
        handleRequestBodyProductionEnded();
}