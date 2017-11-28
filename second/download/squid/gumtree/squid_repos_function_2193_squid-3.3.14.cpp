void
ServerStateData::noteBodyProducerAborted(BodyPipe::Pointer bp)
{
#if USE_ADAPTATION
    if (adaptedBodySource == bp) {
        handleAdaptedBodyProducerAborted();
        return;
    }
#endif
    if (requestBodySource == bp)
        handleRequestBodyProducerAborted();
}