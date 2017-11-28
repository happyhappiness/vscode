void
strup(char *s)
{
    while (*s) {
        *s = (char)toupper((unsigned char) *s);
        ++s;
    }
}