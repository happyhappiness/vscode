static void
lc(char *string)
{
    char *p = string, c;
    while ((c = *p)) {
        *p = xtolower(c);
        p++;
    }
}