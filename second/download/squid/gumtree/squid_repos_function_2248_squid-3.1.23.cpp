void
store_client::operator delete (void *address)
{
    store_client *t = static_cast<store_client *>(address);
    cbdataFree(t);
}