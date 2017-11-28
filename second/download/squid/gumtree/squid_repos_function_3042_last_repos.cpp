void
ConnStateData::noteBodyConsumerAborted(BodyPipe::Pointer )
{
    // request reader may get stuck waiting for space if nobody consumes body
    if (bodyPipe != NULL)
        bodyPipe->enableAutoConsumption();

    // kids extend
}