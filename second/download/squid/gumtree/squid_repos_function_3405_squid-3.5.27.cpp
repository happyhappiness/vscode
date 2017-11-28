void
packerAppend(Packer * p, const char *buf, int sz)
{
    assert(p);
    assert(p->real_handler && p->append);
    p->append(p->real_handler, buf, sz);
}