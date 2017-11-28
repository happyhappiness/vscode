void
Rock::Rebuild::validateOneEntry()
{
    LoadingEntry &e = entries[validationPos];
    switch (e.state) {

    case LoadingEntry::leEmpty:
        break; // no entry hashed to this position

    case LoadingEntry::leLoading:
        freeBadEntry(validationPos, "partially stored");
        break;

    case LoadingEntry::leLoaded:
        break; // we have already unlocked this entry

    case LoadingEntry::leCorrupted:
        break; // we have already removed this entry
    }
}