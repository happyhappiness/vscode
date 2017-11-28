void
DelayVector::stats(StoreEntry * sentry)
{
    iterator pos = pools.begin();

    while (pos != pools.end()) {
        (*pos)->stats(sentry);
        ++pos;
    }
}