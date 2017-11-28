void *
CossRead::operator new (size_t)
{
    CBDATA_INIT_TYPE(CossRead);
    CossRead *result = cbdataAlloc(CossRead);
    return result;
}