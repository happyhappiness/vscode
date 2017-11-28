const char *
StoreEntry::describeTimestamps() const
{
    LOCAL_ARRAY(char, buf, 256);
    snprintf(buf, 256, "LV:%-9d LU:%-9d LM:%-9d EX:%-9d",
             static_cast<int>(timestamp),
             static_cast<int>(lastref),
             static_cast<int>(lastModified_),
             static_cast<int>(expires));
    return buf;
}