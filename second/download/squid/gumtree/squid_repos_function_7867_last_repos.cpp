static struct addrinfo *
dup_addrinfo (struct addrinfo *info, void *addr, size_t addrlen) {
    struct addrinfo *ret;

    ret = (struct addrinfo *)malloc(sizeof (struct addrinfo));
    if (ret == NULL)
        return NULL;
    memcpy (ret, info, sizeof (struct addrinfo));
    ret->ai_addr = (struct sockaddr*)malloc(addrlen);
    if (ret->ai_addr == NULL) {
        free (ret);
        return NULL;
    }
    memcpy (ret->ai_addr, addr, addrlen);
    ret->ai_addrlen = addrlen;
    return ret;
}