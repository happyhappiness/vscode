static int
uuid_init (void)
{
    char *uuid = uuid_get_local ();

    if (uuid) {
        sstrncpy (hostname_g, uuid, DATA_MAX_NAME_LEN);
        sfree (uuid);
        return 0;
    }

    WARNING ("uuid: could not read UUID using any known method");
    return 0;
}