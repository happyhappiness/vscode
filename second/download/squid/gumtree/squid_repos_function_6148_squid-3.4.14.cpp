void
ESIVarState::operator delete (void *address)
{
    cbdataFree (address);
}