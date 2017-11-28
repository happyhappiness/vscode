String::size_type
String::find(char const *aString) const
{
    const char *c;
    c=pos(aString);
    if (c==NULL)
        return npos;
    return c-rawBuf();
}