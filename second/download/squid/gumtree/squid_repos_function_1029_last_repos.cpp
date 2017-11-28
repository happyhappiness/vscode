void
String::allocAndFill(const char *str, int len)
{
    PROF_start(StringAllocAndFill);
    assert(str);
    allocBuffer(len + 1);
    len_ = len;
    memcpy(buf_, str, len);
    buf_[len] = '\0';
    PROF_stop(StringAllocAndFill);
}