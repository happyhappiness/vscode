static void
free_block_devices ()
{
    int i;

    if (block_devices) {
        for (i = 0; i < nr_block_devices; ++i)
            sfree (block_devices[i].path);
        sfree (block_devices);
    }
    block_devices = NULL;
    nr_block_devices = 0;
}