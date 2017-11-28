bool Adaptation::Icap::ModXact::shouldAllow206out()
{
    return shouldAllow206any() && canBackupEverything();
}