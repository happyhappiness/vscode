void *
cbdata::operator new(size_t size, void *where)
{
    // assert (size == sizeof(cbdata));
    return where;
}