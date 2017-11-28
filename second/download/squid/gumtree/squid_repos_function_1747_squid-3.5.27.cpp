const char *
storeEntryFlags(const StoreEntry * entry)
{
    LOCAL_ARRAY(char, buf, 256);
    int flags = (int) entry->flags;
    char *t;
    buf[0] = '\0';

    if (EBIT_TEST(flags, ENTRY_SPECIAL))
        strcat(buf, "SPECIAL,");

    if (EBIT_TEST(flags, ENTRY_REVALIDATE_ALWAYS))
        strcat(buf, "REVALIDATE_ALWAYS,");

    if (EBIT_TEST(flags, DELAY_SENDING))
        strcat(buf, "DELAY_SENDING,");

    if (EBIT_TEST(flags, RELEASE_REQUEST))
        strcat(buf, "RELEASE_REQUEST,");

    if (EBIT_TEST(flags, REFRESH_REQUEST))
        strcat(buf, "REFRESH_REQUEST,");

    if (EBIT_TEST(flags, ENTRY_REVALIDATE_STALE))
        strcat(buf, "REVALIDATE_STALE,");

    if (EBIT_TEST(flags, ENTRY_DISPATCHED))
        strcat(buf, "DISPATCHED,");

    if (EBIT_TEST(flags, KEY_PRIVATE))
        strcat(buf, "PRIVATE,");

    if (EBIT_TEST(flags, ENTRY_FWD_HDR_WAIT))
        strcat(buf, "FWD_HDR_WAIT,");

    if (EBIT_TEST(flags, ENTRY_NEGCACHED))
        strcat(buf, "NEGCACHED,");

    if (EBIT_TEST(flags, ENTRY_VALIDATED))
        strcat(buf, "VALIDATED,");

    if (EBIT_TEST(flags, ENTRY_BAD_LENGTH))
        strcat(buf, "BAD_LENGTH,");

    if (EBIT_TEST(flags, ENTRY_ABORTED))
        strcat(buf, "ABORTED,");

    if ((t = strrchr(buf, ',')))
        *t = '\0';

    return buf;
}