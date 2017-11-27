static int
ignore_device_match (ignorelist_t *il, const char *domname, const char *devpath)
{
    char *name;
    int n, r;

    n = sizeof (char) * (strlen (domname) + strlen (devpath) + 2);
    name = malloc (n);
    if (name == NULL) {
        ERROR ("libvirt plugin: malloc failed.");
        return 0;
    }
    ssnprintf (name, n, "%s:%s", domname, devpath);
    r = ignorelist_match (il, name);
    free (name);
    return r;
}