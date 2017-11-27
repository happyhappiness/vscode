static char *
uuid_get_from_dmidecode(void)
{
    FILE *dmidecode = popen("dmidecode -t system 2>/dev/null", "r");
    char *uuid;

    if (!dmidecode)
        return (NULL);

    uuid = uuid_parse_dmidecode(dmidecode);

    pclose(dmidecode);
    return (uuid);
}