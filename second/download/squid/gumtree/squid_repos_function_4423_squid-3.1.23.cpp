ACLData<protocol_t> *
ACLProtocolData::clone() const
{
    /* Splay trees don't clone yet. */
    assert (!values);
    return new ACLProtocolData(*this);
}