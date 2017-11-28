void
CacheManager::registerProfile(const Mgr::ActionProfile::Pointer &profile)
{
    Must(profile != NULL);
    if (std::find(menu_.begin(), menu_.end(), profile) == menu_.end()) {
        menu_.push_back(profile);
        debugs(16, 3, HERE << "registered profile: " << *profile);
    } else {
        debugs(16, 2, HERE << "skipped duplicate profile: " << *profile);
    }
}