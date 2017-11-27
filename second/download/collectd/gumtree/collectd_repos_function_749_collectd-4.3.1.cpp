static int
uuid_init (void)
{
    char *uuid = uuid_get_local ();

    if (uuid) {
        strncpy (hostname_g, uuid, DATA_MAX_NAME_LEN);
        hostname_g[DATA_MAX_NAME_LEN-1] = '\0';
        sfree (uuid);
        return 0;
    }

    WARNING ("uuid: could not read UUID using any known method");
    return 0;
}