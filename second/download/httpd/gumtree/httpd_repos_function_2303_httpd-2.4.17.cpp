apr_status_t h2_from_h1_destroy(h2_from_h1 *from_h1)
{
    if (from_h1->response) {
        h2_response_destroy(from_h1->response);
        from_h1->response = NULL;
    }
    from_h1->bb = NULL;
    return APR_SUCCESS;
}