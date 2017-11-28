ACLData<char const *> *
ACLRegexData::clone() const
{
    /* Regex's don't clone yet. */
    assert(data.empty());
    return new ACLRegexData;
}