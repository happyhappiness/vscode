String::size_type
String::rfind(char const ch) const
{
    const char *c;
    c=rpos(ch);
    if (c==NULL)
        return npos;
    return c-rawBuf();
}