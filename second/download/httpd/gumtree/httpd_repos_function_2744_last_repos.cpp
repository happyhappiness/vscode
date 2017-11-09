static apr_status_t cleanup_beamers(void *dummy)
{
    (void)dummy;
    beamers = NULL;
    return APR_SUCCESS;
}