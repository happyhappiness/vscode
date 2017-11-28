void BodyProducer::stopProducingFor(RefCount<BodyPipe> &pipe, bool atEof)
{
    debugs(91,7, HERE << this << " will not produce for " << pipe <<
           "; atEof: " << atEof);
    assert(pipe != NULL); // be strict: the caller state may depend on this
    pipe->clearProducer(atEof);
    pipe = NULL;
}