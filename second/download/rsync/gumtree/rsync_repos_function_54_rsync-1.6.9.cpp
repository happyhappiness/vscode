static void
z_free(void *opaque, void *adrs, uInt nbytes)
{
    free(adrs);
}