static int
make_num(const char *s)
{
    if (*s >= '0' && *s <= '9')
        return 10 * (*s - '0') + *(s + 1) - '0';
    else
        return *(s + 1) - '0';
}