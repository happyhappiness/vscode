void
Rock::Rebuild::validateOneEntry(const sfileno fileNo)
{
    LoadingEntry entry = loadingEntry(fileNo);
    switch (entry.state()) {

    case LoadingEntry::leLoading:
        finalizeOrFree(fileNo, entry);
        break;

    case LoadingEntry::leEmpty: // no entry hashed to this position
    case LoadingEntry::leLoaded: // we have already unlocked this entry
    case LoadingEntry::leCorrupted: // we have already removed this entry
    case LoadingEntry::leIgnored: // we have already discarded this entry
        break;
    }
}