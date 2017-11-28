void

StringRegistry::add
(String const *entry)
{
    entries.insert(entry, ptrcmp);
}