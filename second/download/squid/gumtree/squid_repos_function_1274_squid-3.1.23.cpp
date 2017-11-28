void *
ps_state::operator new(size_t)
{
    CBDATA_INIT_TYPE(ps_state);
    return cbdataAlloc(ps_state);
}