static int
add_interface_device (virDomainPtr dom, const char *path, const char *address, unsigned int number)
{
    struct interface_device *new_ptr;
    int new_size = sizeof (interface_devices[0]) * (nr_interface_devices+1);
    char *path_copy, *address_copy, number_string[15];

    if ((path == NULL) || (address == NULL))
        return EINVAL;

    path_copy = strdup (path);
    if (!path_copy) return -1;

    address_copy = strdup (address);
    if (!address_copy) {
        sfree(path_copy);
        return -1;
    }

    snprintf(number_string, sizeof (number_string), "interface-%u", number);

    if (interface_devices)
        new_ptr = realloc (interface_devices, new_size);
    else
        new_ptr = malloc (new_size);

    if (new_ptr == NULL) {
        sfree (path_copy);
        sfree (address_copy);
        return -1;
    }
    interface_devices = new_ptr;
    interface_devices[nr_interface_devices].dom = dom;
    interface_devices[nr_interface_devices].path = path_copy;
    interface_devices[nr_interface_devices].address = address_copy;
    interface_devices[nr_interface_devices].number = strdup(number_string);
    return nr_interface_devices++;
}