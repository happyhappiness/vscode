void
StoreEntry::operator delete (void *address)
{
    pool->freeOne(address);
}