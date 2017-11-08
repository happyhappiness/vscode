apr_status_t h2_from_h1_destroy(h2_from_h1 *from_h1)
{
    from_h1->bb = NULL;
    return APR_SUCCESS;
}