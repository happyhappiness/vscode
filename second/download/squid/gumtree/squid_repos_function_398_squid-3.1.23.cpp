static void
urldecode(char *dst, const char *src, int size)
{
    char tmp[3];
    tmp[2] = '\0';
    while (*src && size > 1) {
        if (*src == '%' && src[1] != '\0' && src[2] != '\0') {
            src++;
            tmp[0] = *src++;
            tmp[1] = *src++;
            *dst++ = strtol(tmp, NULL, 16);
        } else {
            *dst++ = *src++;
        }
        size--;
    }
    *dst++ = '\0';
}