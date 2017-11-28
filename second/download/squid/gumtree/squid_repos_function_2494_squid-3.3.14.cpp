void
FtpStateData::operator delete (void *address)
{
    FtpStateData *t = static_cast<FtpStateData *>(address);
    cbdataFree(t);
}