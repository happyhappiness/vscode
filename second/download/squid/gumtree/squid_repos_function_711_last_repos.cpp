static void
trim_trailing_ws(char* str)
{
    assert(str != NULL);
    unsigned i = strlen(str);
    while ((i > 0) && xisspace(str[i - 1]))
        --i;
    str[i] = '\0';
}