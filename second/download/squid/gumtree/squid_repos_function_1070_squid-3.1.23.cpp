static bool
isUnsignedNumeric(const char *str, size_t len)
{
    if (len < 1) return false;

    for (; len >0 && *str; str++, len--) {
        if (! isdigit(*str))
            return false;
    }
    return true;
}