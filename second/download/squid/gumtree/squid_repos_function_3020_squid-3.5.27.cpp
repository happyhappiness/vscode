void
StoreEntry::clearPrivate()
{
    EBIT_CLR(flags, KEY_PRIVATE);
    shareableWhenPrivate = false;
}