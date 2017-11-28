SBuf &
SBuf::append(const char c)
{
    return lowAppend(&c, 1);
}