void
ExternalACLEntry::operator delete (void *address)
{
    cbdataFree (address);
}