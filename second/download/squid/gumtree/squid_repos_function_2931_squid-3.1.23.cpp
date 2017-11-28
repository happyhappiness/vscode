void
StoreEntry::operator delete (void *address)
{
    pool->free(address);
}