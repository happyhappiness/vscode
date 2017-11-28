void

StringRegistry::remove
(String const *entry)
{
    entries.remove(entry, ptrcmp);
}