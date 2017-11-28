BodyPipe::Pointer
ConnStateData::expectRequestBody(int64_t size)
{
    bodyPipe = new BodyPipe(this);
    bodyPipe->setBodySize(size);
    return bodyPipe;
}