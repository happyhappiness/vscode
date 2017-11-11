static unsigned char parse_hexpair(const char *s)
{
    int result;

    if (isdigit(*s)) {
        result = (*s - '0') << 4;
    }
    else {
        if (isupper(*s)) {
            result = (*s - 'A' + 10) << 4;
        }
        else {
            result = (*s - 'a' + 10) << 4;
        }
    }

    ++s;
    if (isdigit(*s)) {
        result |= (*s - '0');
    }
    else {
        if (isupper(*s)) {
            result |= (*s - 'A' + 10);
        }
        else {
            result |= (*s - 'a' + 10);
        }
    }

    return (unsigned char)result;
}