void
TunnelStateData::operator delete (void *address)
{
    TunnelStateData *t = static_cast<TunnelStateData *>(address);
    cbdataFree(t);
}