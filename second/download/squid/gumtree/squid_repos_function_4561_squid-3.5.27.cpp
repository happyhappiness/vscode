Ssl::ErrorDetailsList::Pointer Ssl::ErrorDetailsManager::getCachedDetails(const char *lang)
{
    Cache::iterator it;
    it = cache.find(lang);
    if (it != cache.end()) {
        debugs(83, 8, HERE << "Found template details in cache for language: " << lang);
        return it->second;
    }

    return NULL;
}