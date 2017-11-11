static const char *set_default_order(cmd_parms *cmd, void *m,
                                     const char *direction, const char *key)
{
    autoindex_config_rec *d_cfg = (autoindex_config_rec *) m;

    if (!strcasecmp(direction, "Ascending")) {
        d_cfg->default_direction = D_ASCENDING;
    }
    else if (!strcasecmp(direction, "Descending")) {
        d_cfg->default_direction = D_DESCENDING;
    }
    else {
        return "First keyword must be 'Ascending' or 'Descending'";
    }

    if (!strcasecmp(key, "Name")) {
        d_cfg->default_keyid = K_NAME;
    }
    else if (!strcasecmp(key, "Date")) {
        d_cfg->default_keyid = K_LAST_MOD;
    }
    else if (!strcasecmp(key, "Size")) {
        d_cfg->default_keyid = K_SIZE;
    }
    else if (!strcasecmp(key, "Description")) {
        d_cfg->default_keyid = K_DESC;
    }
    else {
        return "Second keyword must be 'Name', 'Date', 'Size', or "
               "'Description'";
    }

    return NULL;
}