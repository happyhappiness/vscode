bool Adaptation::Icap::ModXact::canBackupEverything() const
{
    if (!virginBody.expected())
        return true; // no body means no problems with backup

    // if there is a body, check whether we can backup it all

    if (!virginBody.knownSize())
        return false;

    // or should we have a different backup limit?
    // note that '<' allows for 0-termination of the "full" backup buffer
    return virginBody.size() < TheBackupLimit;
}