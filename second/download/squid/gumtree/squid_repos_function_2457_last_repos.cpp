void
StoreEntry::cacheNegatively()
{
    /* This object may be negatively cached */
    negativeCache();
    makePublic();
}