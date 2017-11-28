void
ESIStreamContext::operator delete (void *address)
{
    ESIStreamContext *t = static_cast<ESIStreamContext *>(address);
    cbdataFree(t);
}