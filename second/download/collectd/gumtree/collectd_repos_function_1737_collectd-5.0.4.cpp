static int
uuid_config (const char *key, const char *value)
{
    if (strcasecmp (key, "UUIDFile") == 0) {
        if (uuidfile) {
            ERROR ("UUIDFile given twice in configuration file");
            return 1;
        }
        uuidfile = strdup (value);
        return 0;
    }
    return 0;
}