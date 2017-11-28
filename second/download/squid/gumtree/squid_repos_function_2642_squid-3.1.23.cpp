void *
xmemset(void *dst, int val, size_t sz)
{
    // do debugs output
    debugs(63, 9, "memset: dst=" << dst << ", val=" << val << ", bytes=" << sz);

    // call the system one to do the actual work ~safely.
    return memset(dst, val, sz);
}