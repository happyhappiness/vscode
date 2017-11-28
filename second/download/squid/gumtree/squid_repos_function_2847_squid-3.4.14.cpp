void
CacheManager::registerProfile(const Mgr::ActionProfile::Pointer &profile)
{
    Must(profile != NULL);
    if (!CacheManager::findAction(profile->name)) {
        menu_.push_back(profile);
        debugs(16, 3, HERE << "registered profile: " << *profile);
    } else {
        debugs(16, 2, HERE << "skipped duplicate profile: " << *profile);
    }
}