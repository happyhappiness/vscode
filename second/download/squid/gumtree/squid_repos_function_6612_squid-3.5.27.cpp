void
ESISegment::operator delete (void *address)
{
    cbdataFree (address);
}