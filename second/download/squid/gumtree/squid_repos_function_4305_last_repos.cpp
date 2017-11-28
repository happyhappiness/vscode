ACLData<char const *> *
ACLStringData::clone() const
{
    /* Splay trees don't clone yet. */
    return new ACLStringData(*this);
}