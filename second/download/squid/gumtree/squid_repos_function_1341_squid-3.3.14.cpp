String::size_type
String::find(char const ch) const
{
    const char *c;
    c=pos(ch);
    if (c==NULL)
        return npos;
    return c-rawBuf();
}