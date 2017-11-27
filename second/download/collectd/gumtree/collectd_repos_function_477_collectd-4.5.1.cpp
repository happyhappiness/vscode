static int
add_block_device (virDomainPtr dom, const char *path)
{
    struct block_device *new_ptr;
    int new_size = sizeof (block_devices[0]) * (nr_block_devices+1);
    char *path_copy;

    path_copy = strdup (path);
    if (!path_copy)
        return -1;

    if (block_devices)
        new_ptr = realloc (block_devices, new_size);
    else
        new_ptr = malloc (new_size);

    if (new_ptr == NULL) {
        free (path_copy);
        return -1;
    }
    block_devices = new_ptr;
    block_devices[nr_block_devices].dom = dom;
    block_devices[nr_block_devices].path = path_copy;
    return nr_block_devices++;
}