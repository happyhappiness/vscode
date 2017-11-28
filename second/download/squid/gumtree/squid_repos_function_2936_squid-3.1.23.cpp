const char *
StoreEntry::getMD5Text() const
{
    return storeKeyText((const cache_key *)key);
}