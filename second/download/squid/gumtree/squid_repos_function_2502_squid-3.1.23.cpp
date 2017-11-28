void *
FtpStateData::operator new (size_t)
{
    CBDATA_INIT_TYPE(FtpStateData);
    FtpStateData *result = cbdataAlloc(FtpStateData);
    return result;
}