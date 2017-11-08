static void mpm_main_cleanup(void)
{
    if (pmain) {
        apr_pool_destroy(pmain);
    }
}