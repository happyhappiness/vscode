static void
free_interface_devices ()
{
    int i;

    if (interface_devices) {
        for (i = 0; i < nr_interface_devices; ++i)
            free (interface_devices[i].path);
        free (interface_devices);
    }
    interface_devices = NULL;
    nr_interface_devices = 0;
}