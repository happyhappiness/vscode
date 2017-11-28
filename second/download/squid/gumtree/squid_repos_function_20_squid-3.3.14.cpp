static int
is_number(const char *str)
{
    return strspn(str, "\t -+01234567890./\n") == strlen(str);
}