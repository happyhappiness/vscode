void
BodyPipe::consume(size_t size)
{
    theBuf.consume(size);
    postConsume(size);
}