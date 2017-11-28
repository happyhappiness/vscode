const char *
String::pos(char const *aString) const
{
    if (undefined())
        return NULL;
    return strstr(termedBuf(), aString);
}