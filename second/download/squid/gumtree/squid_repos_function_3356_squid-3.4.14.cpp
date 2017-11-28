void
packerPrintf(Packer * p, const char *fmt,...)
{
    va_list args;
    va_start(args, fmt);

    assert(p);
    assert(p->real_handler && p->packer_vprintf);
    p->packer_vprintf(p->real_handler, fmt, args);
    va_end(args);
}