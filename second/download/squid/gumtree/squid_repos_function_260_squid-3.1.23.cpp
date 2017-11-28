char *
StrnCpy(char *dest, char *src, int n)
{
    char *d = dest;
    if (!dest)
        return (NULL);
    if (!src) {
        *dest = 0;
        return (dest);
    }
    while (n-- && (*d++ = *src++));
    *d = 0;
    return (dest);
}