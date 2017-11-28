void BodyConsumer::stopConsumingFrom(RefCount<BodyPipe> &pipe)
{
    debugs(91,7, HERE << this << " will not consume from " << pipe);
    assert(pipe != NULL); // be strict: the caller state may depend on this
    pipe->clearConsumer();
    pipe = NULL;
}