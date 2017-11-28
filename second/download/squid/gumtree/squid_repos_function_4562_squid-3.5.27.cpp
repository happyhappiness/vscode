void Ssl::ErrorDetailsManager::cacheDetails(ErrorDetailsList::Pointer &errorDetails)
{
    const char *lang = errorDetails->errLanguage.termedBuf();
    assert(lang);
    if (cache.find(lang) == cache.end())
        cache[lang] = errorDetails;
}