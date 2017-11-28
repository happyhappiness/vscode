void
DiskdIOStrategy::statfs(StoreEntry & sentry)const
{
    storeAppendPrintf(&sentry, "Pending operations: %d\n", away);
}