void
acl_access::operator delete (void *address)
{
    acl_access *t = static_cast<acl_access *>(address);
    cbdataFree(t);
}