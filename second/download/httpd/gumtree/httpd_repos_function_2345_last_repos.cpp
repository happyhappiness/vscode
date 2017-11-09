apr_status_t h2_res_create_ngheader(h2_ngheader **ph, apr_pool_t *p,
                                    h2_headers *headers) 
{
    const char *keys[] = {
        ":status"
    };
    const char *values[] = {
        apr_psprintf(p, "%d", headers->status)
    };
    return ngheader_create(ph, p, is_unsafe(headers),  
                           H2_ALEN(keys), keys, values, headers->headers);
}