void
String::allocBuffer(String::size_type sz)
{
    PROF_start(StringInitBuf);
    assert (undefined());
    char *newBuffer = (char*)memAllocString(sz, &sz);
    setBuffer(newBuffer, sz);
    PROF_stop(StringInitBuf);
}