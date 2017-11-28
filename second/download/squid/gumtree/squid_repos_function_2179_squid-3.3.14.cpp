void
ServerStateData::swanSong()
{
    // get rid of our piping obligations
    if (requestBodySource != NULL)
        stopConsumingFrom(requestBodySource);

#if USE_ADAPTATION
    cleanAdaptation();
#endif

    BodyConsumer::swanSong();
#if USE_ADAPTATION
    Initiator::swanSong();
    BodyProducer::swanSong();
#endif

    // paranoid: check that swanSong has been called
    // extra paranoid: yeah, I really mean it. they MUST pass here.
    assert(!requestBodySource);
#if USE_ADAPTATION
    assert(!virginBodyDestination);
    assert(!adaptedBodySource);
#endif
}