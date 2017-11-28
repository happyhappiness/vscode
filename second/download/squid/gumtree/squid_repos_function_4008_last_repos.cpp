bool
ACLNoteData::match(NotePairs::Entry *entry)
{
    if (entry->name.cmp(name.termedBuf()) != 0)
        return false; // name mismatch

    // a name-only note ACL matches any value; others require a values match
    return values->empty() ||
           values->match(entry->value.termedBuf());
}