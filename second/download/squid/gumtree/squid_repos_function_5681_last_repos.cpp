void
CredentialsCache::cleanup()
{
    // cache entries with expiretime <= expirationTime are to be evicted
    const time_t expirationTime =  current_time.tv_sec - ::Config.authenticateTTL;

    const auto end = store_.end();
    for (auto i = store_.begin(); i != end;) {
        debugs(29, 6, "considering " << i->first << "(expires in " <<
               (expirationTime - i->second->expiretime) << " sec)");
        if (i->second->expiretime <= expirationTime) {
            debugs(29, 6, "evicting " << i->first);
            i = store_.erase(i); //erase advances i
        } else {
            ++i;
        }
    }
    gcScheduled_ = false;
    scheduleCleanup();
}