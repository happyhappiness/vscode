void
StoreEntry::lengthWentBad(const char *reason)
{
    debugs(20, 3, "because " << reason << ": " << *this);
    EBIT_SET(flags, ENTRY_BAD_LENGTH);
    releaseRequest();
}