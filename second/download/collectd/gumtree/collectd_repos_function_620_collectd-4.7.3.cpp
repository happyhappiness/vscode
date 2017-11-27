static int
lv_config (const char *key, const char *value)
{
    if (virInitialize () != 0)
        return 1;

    if (il_domains == NULL)
        il_domains = ignorelist_create (1);
    if (il_block_devices == NULL)
        il_block_devices = ignorelist_create (1);
    if (il_interface_devices == NULL)
        il_interface_devices = ignorelist_create (1);

    if (strcasecmp (key, "Connection") == 0) {
        char *tmp = strdup (value);
        if (tmp == NULL) {
            ERROR ("libvirt plugin: Connection strdup failed.");
            return 1;
        }
        sfree (conn_string);
        conn_string = tmp;
        return 0;
    }

    if (strcasecmp (key, "RefreshInterval") == 0) {
        char *eptr = NULL;
        interval = strtol (value, &eptr, 10);
        if (eptr == NULL || *eptr != '\0') return 1;
        return 0;
    }

    if (strcasecmp (key, "Domain") == 0) {
        if (ignorelist_add (il_domains, value)) return 1;
        return 0;
    }
    if (strcasecmp (key, "BlockDevice") == 0) {
        if (ignorelist_add (il_block_devices, value)) return 1;
        return 0;
    }
    if (strcasecmp (key, "InterfaceDevice") == 0) {
        if (ignorelist_add (il_interface_devices, value)) return 1;
        return 0;
    }

    if (strcasecmp (key, "IgnoreSelected") == 0) {
        if (strcasecmp (value, "True") == 0 ||
            strcasecmp (value, "Yes") == 0 ||
            strcasecmp (value, "On") == 0)
        {
            ignorelist_set_invert (il_domains, 0);
            ignorelist_set_invert (il_block_devices, 0);
            ignorelist_set_invert (il_interface_devices, 0);
        }
        else
        {
            ignorelist_set_invert (il_domains, 1);
            ignorelist_set_invert (il_block_devices, 1);
            ignorelist_set_invert (il_interface_devices, 1);
        }
        return 0;
    }

    if (strcasecmp (key, "HostnameFormat") == 0) {
        char *value_copy;
        char *fields[HF_MAX_FIELDS];
        int i, n;

        value_copy = strdup (value);
        if (value_copy == NULL) {
            ERROR ("libvirt plugin: strdup failed.");
            return -1;
        }

        n = strsplit (value_copy, fields, HF_MAX_FIELDS);
        if (n < 1) {
            free (value_copy);
            ERROR ("HostnameFormat: no fields");
            return -1;
        }

        for (i = 0; i < n; ++i) {
            if (strcasecmp (fields[i], "hostname") == 0)
                hostname_format[i] = hf_hostname;
            else if (strcasecmp (fields[i], "name") == 0)
                hostname_format[i] = hf_name;
            else if (strcasecmp (fields[i], "uuid") == 0)
                hostname_format[i] = hf_uuid;
            else {
                free (value_copy);
                ERROR ("unknown HostnameFormat field: %s", fields[i]);
                return -1;
            }
        }
        free (value_copy);

        for (i = n; i < HF_MAX_FIELDS; ++i)
            hostname_format[i] = hf_none;

        return 0;
    }

    /* Unrecognised option. */
    return -1;
}