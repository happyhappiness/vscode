static apr_off_t find_content_length(negotiation_state *neg, var_rec *variant)
{
    apr_finfo_t statb;

    if (variant->bytes < 0) {
        if (   variant->sub_req
            && (variant->sub_req->finfo.valid & APR_FINFO_SIZE)) {
            variant->bytes = variant->sub_req->finfo.size;
        }
        else {
            char *fullname = ap_make_full_path(neg->pool, neg->dir_name,
                                               variant->file_name);

            if (apr_stat(&statb, fullname,
                         APR_FINFO_SIZE, neg->pool) == APR_SUCCESS) {
                variant->bytes = statb.size;
            }
        }
    }

    return variant->bytes;
}