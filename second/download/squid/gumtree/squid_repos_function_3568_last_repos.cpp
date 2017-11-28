void Adaptation::Icap::ModXact::decideOnRetries()
{
    if (!isRetriable)
        return; // no, already decided

    if (preview.enabled())
        return; // yes, because preview provides enough guarantees

    if (canBackupEverything())
        return; // yes, because we can back everything up

    disableRetries(); // no, because we cannot back everything up
}