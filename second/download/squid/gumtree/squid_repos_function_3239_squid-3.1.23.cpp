void
packerToMemInit(Packer * p, MemBuf * mb)
{
    assert(p && mb);
    p->append = (append_f) memBuf_append;
    p->packer_vprintf = (vprintf_f) memBuf_vprintf;
    p->real_handler = mb;
}