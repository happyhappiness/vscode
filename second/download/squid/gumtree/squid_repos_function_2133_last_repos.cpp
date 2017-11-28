static void
htcpHexdump(const char *tag, const char *s, int sz)
{
#if USE_HEXDUMP
    char hex[80];
    debugs(31, 3, "htcpHexdump " << tag);
    memset(hex, '\0', sizeof(hex));

    for (int i = 0; i < sz; ++i) {
        int k = i % 16;
        snprintf(&hex[k * 3], 4, " %02x", (int) *(s + i));

        if (k < 15 && i < (sz - 1))
            continue;

        debugs(31, 3, "\t" << hex);

        memset(hex, '\0', sizeof(hex));
    }
#endif
}