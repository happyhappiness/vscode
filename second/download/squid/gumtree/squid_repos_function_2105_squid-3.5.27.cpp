void BodyConsumer::stopConsumingFrom(RefCount<BodyPipe> &p)
{
    debugs(91,7, this << " will not consume from " << p);
    assert(p != NULL); // be strict: the caller state may depend on this
    p->clearConsumer();
    p = NULL;
}