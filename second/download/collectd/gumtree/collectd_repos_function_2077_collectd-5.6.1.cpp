static int
looks_like_a_uuid (const char *uuid)
{
    int len;

    if (!uuid)
        return (0);

    len = strlen (uuid);

    if (len < UUID_PRINTABLE_COMPACT_LENGTH)
        return (0);

    while (*uuid) {
        if (!isxdigit ((int)*uuid) && *uuid != '-')
            return (0);
        uuid++;
    }
    return (1);
}