void *
CossWrite::operator new (size_t)
{
    CBDATA_INIT_TYPE(CossWrite);
    CossWrite *result = cbdataAlloc(CossWrite);
    return result;
}