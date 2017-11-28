void
mimeEntry::operator delete (void *address)
{
    safe_free (address);
}