template<class RT>
void *
IoResult<RT>::operator new(size_t unused)
{
    CBDATA_INIT_TYPE(IoResult);
    IoResult<RT> *result = cbdataAlloc(IoResult);
    return result;
}