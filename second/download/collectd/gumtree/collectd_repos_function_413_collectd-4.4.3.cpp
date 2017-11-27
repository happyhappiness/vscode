static void
init_value_list (value_list_t *vl, time_t t, virDomainPtr dom)
{
    int i, n;
    const char *name;
    char uuid[VIR_UUID_STRING_BUFLEN];
    char  *host_ptr;
    size_t host_len;

    vl->time = t;
    vl->interval = interval_g;

    strncpy (vl->plugin, "libvirt", sizeof (vl->plugin));
    vl->plugin[sizeof (vl->plugin) - 1] = '\0';

    vl->host[0] = '\0';
    host_ptr = vl->host;
    host_len = sizeof (vl->host);

    /* Construct the hostname field according to HostnameFormat. */
    for (i = 0; i < HF_MAX_FIELDS; ++i) {
        if (hostname_format[i] == hf_none)
            continue;

        n = DATA_MAX_NAME_LEN - strlen (vl->host) - 2;

        if (i > 0 && n >= 1) {
            strncat (vl->host, ":", 1);
            n--;
        }

        switch (hostname_format[i]) {
        case hf_none: break;
        case hf_hostname:
            strncat (vl->host, hostname_g, n);
            break;
        case hf_name:
            name = virDomainGetName (dom);
            if (name)
                strncat (vl->host, name, n);
            break;
        case hf_uuid:
            if (virDomainGetUUIDString (dom, uuid) == 0)
                strncat (vl->host, uuid, n);
            break;
        }
    }

    vl->host[sizeof (vl->host) - 1] = '\0';
}