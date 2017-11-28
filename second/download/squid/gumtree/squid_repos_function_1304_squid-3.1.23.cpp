const char *
String::pos(char const ch) const
{
    if (undefined())
        return NULL;
    return strchr(termedBuf(), ch);
}