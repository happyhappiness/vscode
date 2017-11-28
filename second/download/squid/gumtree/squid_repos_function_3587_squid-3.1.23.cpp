void
MemBuf::init(mb_size_t szInit, mb_size_t szMax)
{
    assert(szInit > 0 && szMax > 0);
    buf = NULL;
    size = 0;
    max_capacity = szMax;
    capacity = 0;
    stolen = 0;
    grow(szInit);
}