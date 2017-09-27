static void show_compile_settings(void)
{
    printf("Server version: %s\n", ap_get_server_description());
    printf("Server built:   %s\n", ap_get_server_built());
    printf("Server's Module Magic Number: %u:%u\n",
           MODULE_MAGIC_NUMBER_MAJOR, MODULE_MAGIC_NUMBER_MINOR);
#if APR_MAJOR_VERSION >= 2
    printf("Server loaded:  APR %s\n", apr_version_string());
    printf("Compiled using: APR %s\n", APR_VERSION_STRING);
#else
    printf("Server loaded:  APR %s, APR-UTIL %s\n",
           apr_version_string(), apu_version_string());
    printf("Compiled using: APR %s, APR-UTIL %s\n",
           APR_VERSION_STRING, APU_VERSION_STRING);
#endif
    /* sizeof(foo) is long on some platforms so we might as well
     * make it long everywhere to keep the printf format
     * consistent
     */
    printf("Architecture:   %ld-bit\n", 8 * (long)sizeof(void *));

