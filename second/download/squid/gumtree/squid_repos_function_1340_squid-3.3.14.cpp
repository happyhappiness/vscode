const char *
String::rpos(char const ch) const
{
    if (undefined())
        return NULL;
    return strrchr(termedBuf(), (ch));
}