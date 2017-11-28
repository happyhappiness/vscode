void
CredentialsCache::scheduleCleanup()
{
    if (!gcScheduled_ && store_.size()) {
        gcScheduled_ = true;
        eventAdd(cacheCleanupEventName, &CredentialsCache::Cleanup,
                 this, ::Config.authenticateGCInterval, 1);
    }
}