int h2_mpm_supported(void)
{
    check_modules(0);
    return mpm_supported;
}