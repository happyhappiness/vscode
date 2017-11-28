void
MemObject::checkUrlChecksum () const
{
    assert(chksum == url_checksum(urlXXX()));
}