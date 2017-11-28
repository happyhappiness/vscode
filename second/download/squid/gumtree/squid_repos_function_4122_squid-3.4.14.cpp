bool Adaptation::Icap::ModXact::fillVirginHttpHeader(MemBuf &mb) const
{
    if (virgin.header == NULL)
        return false;

    virgin.header->firstLineBuf(mb);

    return true;
}