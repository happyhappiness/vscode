static const char *
inet_ntop4(const u_char *src, char *dst, size_t size)
{
    static const char fmt[] = "%u.%u.%u.%u";
    char tmp[sizeof("255.255.255.255")+1];

    if ((size_t)snprintf(tmp, min(sizeof(tmp),size), fmt, src[0], src[1], src[2], src[3]) >= size) {
        errno = ENOSPC;
        return (NULL);
    }
    strcpy(dst, tmp);
    return (dst);
}