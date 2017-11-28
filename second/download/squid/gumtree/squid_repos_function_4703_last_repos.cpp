inline char *
SBufToCstring(const SBuf &s)
{
    char *d = static_cast<char*>(xmalloc(s.length()+1));
    SBufToCstring(d, s);
    return d;
}