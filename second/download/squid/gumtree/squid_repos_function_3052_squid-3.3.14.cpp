void
NullStoreEntry::operator delete(void*)
{
    fatal ("Attempt to delete NullStoreEntry\n");
}