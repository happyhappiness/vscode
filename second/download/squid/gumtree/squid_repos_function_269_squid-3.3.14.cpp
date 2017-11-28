void
strup(char *s)
{
    while (*s) {
        *s = toupper((unsigned char) *s);
        ++s;
    }
}