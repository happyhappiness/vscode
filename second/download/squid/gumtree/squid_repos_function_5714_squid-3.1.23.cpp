void
Tolower(char *q)
{
    char *s = q;

    while (*s) {
        *s = xtolower(*s);
        s++;
    }
}