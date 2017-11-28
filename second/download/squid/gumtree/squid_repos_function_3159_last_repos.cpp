bool StoreIOState::touchingStoreEntry() const
{
    return e && e->swap_filen == swap_filen;
}