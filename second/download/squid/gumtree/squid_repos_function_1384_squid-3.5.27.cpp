int
stringHasWhitespace(const char *s)
{
    return strpbrk(s, w_space) != NULL;
}