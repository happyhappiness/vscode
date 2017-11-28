libecap::Area
Adaptation::Ecap::XactionRep::vbContent(libecap::size_type o, libecap::size_type s)
{
    // We may not be makingVb yet. It should be OK, but see vbContentShift().

    const BodyPipePointer &p = theVirginRep.raw().body_pipe;
    Must(p != NULL);

    // TODO: make MemBuf use size_t?
    const size_t haveSize = static_cast<size_t>(p->buf().contentSize());

    // convert to Squid types; XXX: check for overflow
    const uint64_t offset = static_cast<uint64_t>(o);
    Must(offset <= haveSize); // equal iff at the end of content

    // nsize means no size limit: all content starting from offset
    const size_t size = s == libecap::nsize ?
                        haveSize - offset : static_cast<size_t>(s);

    // XXX: optimize by making theBody a shared_ptr (see Area::FromTemp*() src)
    return libecap::Area::FromTempBuffer(p->buf().content() + offset,
                                         min(static_cast<size_t>(haveSize - offset), size));
}