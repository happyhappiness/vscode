void
CacheManager::StateFree(cachemgrStateData * mgr)
{
    safe_free(mgr->action);
    safe_free(mgr->user_name);
    safe_free(mgr->passwd);
    mgr->entry->unlock();
    xfree(mgr);
}