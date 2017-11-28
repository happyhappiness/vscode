ACLData<char const *> *
ACLStringData::clone() const
{
    /* Splay trees don't clone yet. */
    assert (!values);
    return new ACLStringData(*this);
}