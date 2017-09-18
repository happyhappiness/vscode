static void show_compile_settings(void)
{
    printf("Server version: %s\n", ap_get_server_version());
    printf("Server built:   %s\n", ap_get_server_built());
    printf("Server's Module Magic Number: %u:%u\n",
           MODULE_MAGIC_NUMBER_MAJOR, MODULE_MAGIC_NUMBER_MINOR);

    /* sizeof(foo) is long on some platforms so we might as well
     * make it long everywhere to keep the printf format
     * consistent
     */
    printf("Architecture:   %ld-bit\n", 8 * (long)sizeof(void *));
    printf("Server compiled with....\n");
