void
StoreEntry::lock(const char *context)
{
    ++lock_count;
    debugs(20, 3, context << " locked key " << getMD5Text() << ' ' << *this);
}