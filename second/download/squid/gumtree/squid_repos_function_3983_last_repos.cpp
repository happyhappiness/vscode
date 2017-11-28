ACLData<char const *> *
ACLDomainData::clone() const
{
    /* Splay trees don't clone yet. */
    assert (!domains);
    return new ACLDomainData;
}