void
PeerDigest::operator delete (void *address)
{
    PeerDigest *t = static_cast<PeerDigest *>(address);
    cbdataFree(t);
}