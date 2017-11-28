StoreEntry *

SwapDir::get
(const cache_key *key)
{
    return Store::Root().get(key);
}