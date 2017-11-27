static int
add_interface_device (virDomainPtr dom, const char *path)
{
    struct interface_device *new_ptr;
    int new_size = sizeof (interface_devices[0]) * (nr_interface_devices+1);
    char *path_copy;

    path_copy = strdup (path);
    if (!path_copy) return -1;

    if (interface_devices)
        new_ptr = realloc (interface_devices, new_size);
    else
        new_ptr = malloc (new_size);

    if (new_ptr == NULL) {
        free (path_copy);
        return -1;
    }
    interface_devices = new_ptr;
    interface_devices[nr_interface_devices].dom = dom;
    interface_devices[nr_interface_devices].path = path_copy;
    return nr_interface_devices++;
}