ACLIP::operator delete (void *address)
{
    fatal ("ACLIP::operator delete: unused");
}

/**
 * print/format an acl_ip_data structure for debugging output.
 *
 \param buf string buffer to write to
 \param len size of the buffer available
 */
void
acl_ip_data::toStr(char *buf, int len) const
{
    char *b1 = buf;
    char *b2 = NULL;
