static int xencpu_shutdown (void)
{
    free(cpu_states);
    free(cpu_info);
    xc_interface_close(xc_handle);

    return 0;
}