static apr_table_t *h2_sos_mplx_get_trailers(h2_sos *sos)
{
    h2_sos_mplx *msos = sos->ctx;

    return msos->trailers;
}