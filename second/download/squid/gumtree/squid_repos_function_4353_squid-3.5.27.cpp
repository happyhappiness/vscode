static bool
isKeyNameChar(char c)
{
    if (c >= 'a' && c <= 'z')
        return true;

    if (c >= 'A' && c <= 'Z')
        return true;

    if (c >= '0' && c <= '9')
        return true;

    if (c == '-' || c == '_')
        return true;

    // prevent other characters matching the key=value
    return false;
}