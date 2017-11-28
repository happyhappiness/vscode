static void
htcpHexdump(const char *tag, const char *s, int sz)
{
#if USE_HEXDUMP
    int i;
    int k;
    char hex[80];
    debugs(31, 3, "htcpHexdump " << tag);
    memset(hex, '\0', 80);

    for (i = 0; i < sz; i++) {
        k = i % 16;
        snprintf(&hex[k * 3], 4, " %02x", (int) *(s + i));

        if (k < 15 && i < (sz - 1))
            continue;

        debugs(31, 3, "\t" << hex);

        memset(hex, '\0', 80);
    }

#endif
}