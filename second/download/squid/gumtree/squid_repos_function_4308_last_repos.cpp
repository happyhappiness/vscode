ACLData<char const *> *
ACLServerNameData::clone() const
{
    /* Splay trees don't clone yet. */
    assert (!domains);
    return new ACLServerNameData;
}