void BodyProducer::stopProducingFor(RefCount<BodyPipe> &p, bool atEof)
{
    debugs(91,7, this << " will not produce for " << p << "; atEof: " << atEof);
    assert(p != NULL); // be strict: the caller state may depend on this
    p->clearProducer(atEof);
    p = NULL;
}