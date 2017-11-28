static ssize_t
htcpBuildAuth(char *buf, size_t buflen)
{
    htcpAuthHeader auth;
    size_t copy_sz = 0;
    assert(2 == sizeof(u_int16_t));
    auth.length = htons(2);
    copy_sz += 2;
    if (buflen < copy_sz)
        return -1;
    xmemcpy(buf, &auth, copy_sz);
    return copy_sz;
}