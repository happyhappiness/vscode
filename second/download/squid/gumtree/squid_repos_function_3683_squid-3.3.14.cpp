void
UrnState::operator delete (void *address)
{
    UrnState * tmp = (UrnState *)address;
    cbdataFree (tmp);
}