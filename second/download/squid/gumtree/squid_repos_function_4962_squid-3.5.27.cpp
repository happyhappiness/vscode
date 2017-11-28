ACLData<AnyP::ProtocolType> *
ACLProtocolData::clone() const
{
    /* Splay trees don't clone yet. */
    assert (!values);
    return new ACLProtocolData(*this);
}