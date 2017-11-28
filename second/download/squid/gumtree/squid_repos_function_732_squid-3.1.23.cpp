void
ClientHttpRequest::operator delete (void *address)
{
    ClientHttpRequest *t = static_cast<ClientHttpRequest *>(address);
    cbdataFree(t);
}