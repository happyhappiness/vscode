void
String::allocAndFill(const char *str, int len)
{
    PROF_start(StringAllocAndFill);
    assert(this && str);
    allocBuffer(len + 1);
    len_ = len;
    xmemcpy(buf_, str, len);
    buf_[len] = '\0';
    PROF_stop(StringAllocAndFill);
}