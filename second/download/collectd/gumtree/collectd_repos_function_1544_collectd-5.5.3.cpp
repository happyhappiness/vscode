static int parse_keys (char *buffer, size_t buffer_size, const char *key_str)
{
    char tmp[2 * buffer_size];

    if (buffer == NULL || buffer_size == 0 || key_str == NULL || strlen (key_str) == 0)
        return EINVAL;

    if ((count_parts (key_str) > 2) && has_suffix (key_str, ".type"))
    {
        /* strip ".type" suffix iff the key has more than two parts. */
        size_t sz = strlen (key_str) - strlen (".type") + 1;

        if (sz > sizeof (tmp))
            sz = sizeof (tmp);
        sstrncpy (tmp, key_str, sz);
    }
    else
    {
        sstrncpy (tmp, key_str, sizeof (tmp));
    }

    return compact_ds_name (buffer, buffer_size, tmp);
}