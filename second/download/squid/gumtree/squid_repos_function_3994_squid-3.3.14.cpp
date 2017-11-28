void
Adaptation::Ecap::XactionRep::vbContentShift(libecap::size_type n)
{
    // We may not be makingVb yet. It should be OK now, but if BodyPipe
    // consume() requirements change, we would have to return empty vbContent
    // until the adapter registers as a consumer

    BodyPipePointer &p = theVirginRep.raw().body_pipe;
    Must(p != NULL);
    const size_t size = static_cast<size_t>(n); // XXX: check for overflow
    const size_t haveSize = static_cast<size_t>(p->buf().contentSize()); // TODO: make MemBuf use size_t?
    p->consume(min(size, haveSize));
}