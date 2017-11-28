ACLData<AnyP::ProtocolType> *
ACLProtocolData::clone() const
{
    /* Splay trees don't clone yet. */
    assert(values.empty());
    return new ACLProtocolData(*this);
}