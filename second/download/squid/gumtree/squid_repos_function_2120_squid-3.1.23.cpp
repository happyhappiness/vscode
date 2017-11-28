void
ServerStateData::noteMoreBodyDataAvailable(BodyPipe::Pointer bp)
{
#if USE_ADAPTATION
    if (adaptedBodySource == bp) {
        handleMoreAdaptedBodyAvailable();
        return;
    }
#endif
    if (requestBodySource == bp)
        handleMoreRequestBodyAvailable();
}