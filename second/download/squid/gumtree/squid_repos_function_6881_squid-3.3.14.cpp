static const char *
inet_ntop4(src, dst, size)
const u_char *src;
char *dst;
size_t size;
{
    static const char fmt[] = "%u.%u.%u.%u";
    char tmp[sizeof "255.255.255.255"];

    if (snprintf(tmp, min(sizeof("255.255.255.255"),size), fmt, src[0], src[1], src[2], src[3]) >= size) {
        errno = ENOSPC;
        return (NULL);
    }
    strcpy(dst, tmp);
    return (dst);
}