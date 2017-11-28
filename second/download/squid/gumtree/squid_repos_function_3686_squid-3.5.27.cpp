BodyPipe::Pointer
ConnStateData::expectRequestBody(int64_t size)
{
    bodyPipe = new BodyPipe(this);
    if (size >= 0)
        bodyPipe->setBodySize(size);
    else
        startDechunkingRequest();
    return bodyPipe;
}