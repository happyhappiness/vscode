ACLData<char const *> *
ACLUserData::clone() const
{
    /* Splay trees don't clone yet. */
    assert (!names);
    return new ACLUserData;
}