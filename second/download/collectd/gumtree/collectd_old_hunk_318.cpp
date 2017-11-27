lv_read (void)
{
    time_t t;
    int i;

    if (conn == NULL) {
        ERROR ("libvirt plugin: Not connected. Use Connection in "
                "config file to supply connection URI.  For more information "
                "see <http://libvirt.org/uri.html>");
        return -1;
    }

    time (&t);

    /* Need to refresh domain or device lists? */
    if ((last_refresh == (time_t) 0) ||
            ((interval > 0) && ((last_refresh + interval) <= t))) {
        if (refresh_lists () != 0)
            return -1;
        last_refresh = t;
    }

#if 0
    for (i = 0; i < nr_domains; ++i)
        fprintf (stderr, "domain %s\n", virDomainGetName (domains[i]));
