static const char *
describeTimestamps(const StoreEntry * entry)
{
    LOCAL_ARRAY(char, buf, 256);
    snprintf(buf, 256, "LV:%-9d LU:%-9d LM:%-9d EX:%-9d",
             (int) entry->timestamp,
             (int) entry->lastref,
             (int) entry->lastmod,
             (int) entry->expires);
    return buf;
}