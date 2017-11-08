static apr_status_t random_pick(apr_uint32_t *number,
                                apr_uint32_t min,
                                apr_uint32_t max)
{
    apr_status_t rv = 
        apr_generate_random_bytes((void*)number, sizeof(apr_uint32_t));

    if (rv) {
        return rv;
    }

    RAND_RANGE(*number, min, max, APR_UINT32_MAX);

    return APR_SUCCESS;
}