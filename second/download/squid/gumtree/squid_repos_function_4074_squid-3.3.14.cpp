bool Adaptation::Icap::ModXact::shouldAllow204()
{
    if (!service().allows204())
        return false;

    return canBackupEverything();
}