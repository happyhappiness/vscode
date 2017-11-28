void
uc(char *string)
{
    char *p = string, c;
    while ((c = *p)) {
        *p = xtoupper(c);
        p++;
    }
}