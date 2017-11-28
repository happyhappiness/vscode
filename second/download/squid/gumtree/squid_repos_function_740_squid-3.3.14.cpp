void
ClientRequestContext::operator delete (void *address)
{
    ClientRequestContext *t = static_cast<ClientRequestContext *>(address);
    cbdataFree(t);
}