static char *
uuid_get_from_sysctl(void)
{
    char uuid[UUID_PRINTABLE_NORMAL_LENGTH + 1];
    size_t len = sizeof (uuid);
    int mib[2];

    mib[0] = CTL_HW;
    mib[1] = HW_UUID;

    if (sysctl(mib, 2, uuid, &len, NULL, 0) == -1)
        return NULL;
    return (strdup (uuid));
}