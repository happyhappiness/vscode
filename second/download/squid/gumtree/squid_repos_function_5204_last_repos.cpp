bool
Client::abortOnBadEntry(const char *abortReason)
{
    if (entry->isAccepting())
        return false;

    debugs(11,5, HERE << "entry is not Accepting!");
    abortOnData(abortReason);
    return true;
}