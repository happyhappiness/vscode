static int
lv_shutdown (void)
{
    free_block_devices ();
    free_interface_devices ();
    free_domains ();

    if (conn != NULL)
        virConnectClose (conn);
    conn = NULL;

    ignorelist_free (il_domains);
    il_domains = NULL;
    ignorelist_free (il_block_devices);
    il_block_devices = NULL;
    ignorelist_free (il_interface_devices);
    il_interface_devices = NULL;

    return 0;
}