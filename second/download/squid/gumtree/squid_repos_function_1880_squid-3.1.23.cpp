StoreEntry *

StoreController::get
(const cache_key *key)
{

    return swapDir->get
           (key);
}