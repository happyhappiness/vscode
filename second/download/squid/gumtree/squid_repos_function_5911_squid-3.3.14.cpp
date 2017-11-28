void
ESIContext::operator delete (void *address)
{
    ESIContext *t = static_cast<ESIContext *>(address);
    cbdataFree(t);
}