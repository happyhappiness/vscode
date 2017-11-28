char const *
trim (char const *s)
{
    while (*s == ' ')
        ++s;

    return s;
}