static apr_table_t *h2_sos_h2_status_get_trailers(h2_sos *sos)
{
    return sos->prev->get_trailers(sos->prev);
}